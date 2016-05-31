/*
 * CandidateService.cpp
 *
 *  Created on: May 24, 2016
 *      Author: ediaz
 */

#include "CandidateService.h"

CandidateService::CandidateService(shared_ptr<DataBase> DB) {
	shared_ptr<UserDao> userDaoAux(new UserDao(DB));
	userDao = userDaoAux;
}

CandidateService::~CandidateService() {
	// TODO Auto-generated destructor stub
}

search_candidate_t CandidateService::searchCandidate(string idUser){
	search_candidate_t search_candidate;
	vector<User> candidates;

	//Obtengo el usuario asociado a este id
	User user = userDao->getUser(idUser);

	//Verifico limite diario
	if (user.getQuantitySearchDaily() >= MAX_SEARCH_CANDIDATE){
		//Excede busqueda
		search_candidate.change(ERROR_LIMIT_DAILY, candidates);

		return search_candidate;
	}

	//Actualizo limite diario
	user = userDao->increaseQuantitySearchDaily(user);

	//Obtengo todos los usuarios cargados localmente
	candidates = userDao->getCandidatesForIdUser(idUser);

	//Me quedo con el XX% menos votados
	candidates = getUsersLeastVoted(candidates);

	//Saco los que tuvieron un match en comun
	candidates = getUsersNotMatch(user, candidates);

	//Filtro por cercania. Me quedo con los que estan mas cerca
	candidates = getUsersNear(user, candidates);

	//Me quedo con los que tengan algun interes en comun
	candidates = getUsersCommonInterests(user, candidates);

	search_candidate.change(OK_SEARCH, candidates);

	return search_candidate;
}

vector<User> CandidateService::getUsersLeastVoted(vector<User> candidates){
	/*
	 * Me quedo con el XX% menos votados
	 * Ejemplo:
	 * 		Tengo 200 usuarios
	 * 		Porcentaje de mas votados a descartar = 1%
	 * 		Entonces se tiene que 200 * 1% = 2 usuarios
	 * 		Por lo tanto, se van a dejar afuera los 2 usuarios con mas matchs.
	 */

	cout<< "Cantidad de candidatos:" << candidates.size() << endl;
	cout<< "Porcentaje:" << PERCENTAGE_LEAST_VOTED << endl;
	cout<< "Cantidad * Porcentaje:" << (candidates.size() * PERCENTAGE_LEAST_VOTED)  << endl;

	double div = (double)((candidates.size() * PERCENTAGE_LEAST_VOTED)/ 100);
	cout<< "(Cantidad * Porcentaje) / 100:" << div  << endl;
	int quantity = round(div);

	if (quantity == 0){
		return candidates;
	}

	sort(candidates.begin(), candidates.end());

	vector<User> candidatesOk;
	for (int i = (candidates.size() - 1); i >=0; i--){
		if (quantity > 0){
			quantity --;
		} else {
			//Me quedo con los candidatos con menos matchs
			candidatesOk.push_back(candidates[i]);
		}
	}

	return candidatesOk;
}

vector<User> CandidateService::getUsersNotMatch(User user, vector<User> candidates){
	/*
	 * Saco los que tuvieron un match en comun.
	 */
	vector<User> candidatesOk;

	for(int i = 0; i < candidates.size(); i++){
		User candidate = candidates[i];
		vector<string>::const_iterator vMatchIt(candidate.getIdUserMatchs().begin()), vMatchEnd(candidate.getIdUserMatchs().end());
		bool match = false;
		for (; vMatchIt != vMatchEnd; ++vMatchIt){
			string idUserMatch = *vMatchIt;
			if (idUserMatch.compare(user.getId().c_str()) == 0){
				match = true;
				break;
			}
		}

		if (!match){
			candidatesOk.push_back(candidate);
		}
	}

	return candidatesOk;
}

vector<User> CandidateService::getUsersNear(User user, vector<User> candidates){
	/*
	 * Filtro por cercania. Me quedo con los que estan mas cerca.
	 */

	vector<User> candidatesOk;
	vector<User>::const_iterator vit(candidates.begin()), vend(candidates.end());

	for(; vit != vend; ++vit){
		User candidate = *vit;

		double distanceLatitude = fabs(fabs(user.getLatitude()) - fabs(candidate.getLatitude()));
		if (distanceLatitude > MAX_LATITUDE){
			continue;
		}

		double distanceLongitude = fabs(fabs(user.getLongitude()) - fabs(candidate.getLongitude()));
		if (distanceLongitude > MAX_LONGITUDE){
			continue;
		}

		candidatesOk.push_back(candidate);
	}

	return candidatesOk;
}

vector<User> CandidateService::getUsersCommonInterests(User user, vector<User> candidates){
	/*
	 * Me quedo con los que tengan algun interes en comun.
	 */
	vector<User> candidatesOk;
	vector<User>::const_iterator vit(candidates.begin()), vend(candidates.end());

	//Recorro los candidatos
	for(; vit != vend; ++vit){
		User candidate = *vit;

		vector<Interest> candidateInterests = candidate.getInterests();
		bool commonInterests = false;

		//Voy a recorrer los intereses del usuario
		vector<Interest>::const_iterator vUserInterestIt(user.getInterests().begin()) , vUserInterestEnd(user.getInterests().end());
		for(; vUserInterestIt != vUserInterestEnd; ++vUserInterestIt){
			Interest userInterest = *vUserInterestIt;

			//Voy a recorrer los intereses del candidato en busca de coincidencias
			vector<Interest>::const_iterator vCandidateInterestIt(candidateInterests.begin()) ,
					vCandidateInterestEnd(candidateInterests.end());
			for(; vCandidateInterestIt != vCandidateInterestEnd; ++vCandidateInterestIt){
				Interest candidateInterest = *vCandidateInterestIt;

				if (userInterest.getCategory().compare(candidateInterest.getCategory().c_str()) == 0
						&& userInterest.getValue().compare(candidateInterest.getValue().c_str()) == 0){
					//Hay coincidencia
					commonInterests = true;
					break;
				}
			}

			if (commonInterests){
				break;
			}
		}

		if (commonInterests){
			candidatesOk.push_back(candidate);
		}
	}

	return candidatesOk;
}

StatusCodeMatch CandidateService::match(string idUser, string idUserMatch){
	this->userDao->putMatch(idUser, idUserMatch);
	return StatusCodeMatch::OK_UPDATE_MATCH;
}
