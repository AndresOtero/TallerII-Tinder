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
	LOG(INFO) << "Comienzo a buscar candidatos a match (CandidateService - searchCandidate).";
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

	LOG(DEBUG) << "Cantidad de candidatos inicial (CandidateService - searchCandidate): " << candidates.size();

	//Me quedo con el XX% menos votados
	candidates = getUsersLeastVoted(candidates);

	//Saco los que tuvieron un match en comun
	candidates = getUsersNotMatch(user, candidates);

	//Filtro por cercania. Me quedo con los que estan mas cerca
	candidates = getUsersNear(user, candidates);

	//Me quedo con los que tengan algun interes en comun
	candidates = getUsersCommonInterests(user, candidates);

	search_candidate.change(OK_SEARCH, candidates);

	LOG(INFO) << "Fin de busqueda de candidatos a match (CandidateService - searchCandidate).";
	return search_candidate;
}

vector<User> CandidateService::getUsersLeastVoted(vector<User> candidates){
	/*
	 * Me quedo con el XX% menos votados
	 * Ejemplo:
	 * 		Tengo 200 usuarios que tienen algun match hecho
	 * 		Porcentaje de mas votados a descartar = 1%
	 * 		Entonces se tiene que 200 * 1% = 2 usuarios
	 * 		Por lo tanto, se van a dejar afuera los 2 usuarios con mas matchs.
	 */
	LOG(DEBUG) << "Se van a sacar los candidatos con mayor cantidad de matchs (CandidateService - getUsersLeastVoted).";

	double quantityCandidates = candidates.size();
	double percentage = PERCENTAGE_LEAST_VOTED;
	double denominate = 100;

	double div = (double)((quantityCandidates * percentage)/ denominate);
	cout<< "(Cantidad * Porcentaje) / 100:" << div  << endl;
	int quantity = round(div);

	cout<< "quantity - para sacar:" << quantity  << endl;

	if (quantity == 0){
		LOG(DEBUG) << "Cantidad de candidatos con menos matchs que quedaron (CandidateService - getUsersLeastVoted): " << candidates.size();
		return candidates;
	}

	//Verifico los usuarios que tienen algun match
	vector<User> candidatesWithMatch;
	for(User candidate : candidates){
		if (!candidate.getIdUserMatchs().empty()){
			candidatesWithMatch.push_back(candidate);
		}
	}

	if (candidatesWithMatch.empty()){
		LOG(DEBUG) << "Cantidad de candidatos con menos matchs que quedaron (CandidateService - getUsersLeastVoted): " << candidates.size();
		return candidates;
	}

	sort(candidatesWithMatch.begin(), candidatesWithMatch.end());

	/*
	 * Me quedo con los candidatos que deberia de eliminar de la lista de
	 * candidatos ok, que serian los que mas matchs tienen.
	 */
	vector<User> candidatesExclude;
	for (int i = (candidatesExclude.size() - 1); i >=0; i--){
		if (quantity > 0){
			quantity --;
			candidatesExclude.push_back(candidatesExclude[i]);
		}
	}

	/*
	 * Limpio la lista de candidatos: me quedo efectivamente con los que menos matchs tienen.
	 */
	vector<User> candidatesOk;
	for (int i = 0; i < candidates.size(); i++){
		User candidate = candidates[i];
		int iExcl = 0;
		bool find = false;
		while (iExcl < candidatesExclude.size() && !find){
			User candidateExcl = candidatesExclude[iExcl];
			if(candidateExcl.getId().compare(candidate.getId().c_str()) == 0){
				find = true;
			}
			iExcl++;
		}

		if(!find){
			//Me quedo con los candidatos con menos matchs
			candidatesOk.push_back(candidate);
		}
	}

	LOG(DEBUG) << "Cantidad de candidatos con menos matchs que quedaron (CandidateService - getUsersLeastVoted): " << candidatesOk.size();
	return candidatesOk;
}

vector<User> CandidateService::getUsersNotMatch(User user, vector<User> candidates){
	/*
	 * Saco los que tuvieron un match en comun.
	 */
	LOG(DEBUG) << "Se van a sacar los candidatos con los que ya tuvo match (CandidateService - getUsersNotMatch).";
	vector<User> candidatesOk;

	for(int i = 0; i < candidates.size(); i++){
		User candidate = candidates[i];
		bool match = false;
		if (!candidate.getIdUserMatchs().empty()){
			int iMatch = 0;
			while (iMatch < candidate.getIdUserMatchs().size() && !match){
				string idUserMatch = candidate.getIdUserMatchs()[iMatch];
				if (idUserMatch.compare(user.getId().c_str()) == 0){
					match = true;
				}
				iMatch++;
			}
		}

		if (!match){
			candidatesOk.push_back(candidate);
		}
	}

	LOG(DEBUG) << "Cantidad de candidatos con los que no tuvo match (CandidateService - getUsersNotMatch):" << candidatesOk.size();
	return candidatesOk;
}

vector<User> CandidateService::getUsersNear(User user, vector<User> candidates){
	/*
	 * Filtro por cercania. Me quedo con los que estan mas cerca.
	 */
	LOG(DEBUG) << "Se van a dejar los candidatos que se encuentren mas cerca (CandidateService - getUsersNear).";
	vector<User> candidatesOk;

	for(int iCand = 0; iCand < candidates.size(); iCand++){
		User candidate = candidates[iCand];

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

	LOG(DEBUG) << "Cantidad de candidatos mas cerca (CandidateService - getUsersNear): " << candidatesOk.size();
	return candidatesOk;
}

vector<User> CandidateService::getUsersCommonInterests(User user, vector<User> candidates){
	/*
	 * Me quedo con los que tengan algun interes en comun.
	 */
	LOG(DEBUG) << "Se van a dejar los candidatos con los que tenga algun interes en comun (CandidateService - getUsersCommonInterests).";
	vector<User> candidatesOk;

	//Recorro los candidatos
	for(int icand = 0; icand < candidates.size(); icand++){
		User candidate = candidates[icand];
		bool commonInterests = false;

		//Voy a recorrer los intereses del usuario
		for(int iUseInt = 0; iUseInt < user.getInterests().size(); iUseInt ++){
			Interest userInterest = user.getInterests()[iUseInt];

			//Voy a recorrer los intereses del candidato en busca de coincidencias
			for(int iCandInt = 0; iCandInt < candidate.getInterests().size(); iCandInt ++){
				Interest candidateInterest = candidate.getInterests()[iCandInt];

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

	LOG(DEBUG) << "Cantidad de candidatos con los que tiene algun interes en comun (CandidateService - getUsersCommonInterests): " << candidatesOk.size();
	return candidatesOk;
}

StatusCodeMatch CandidateService::match(string idUser, string idUserMatch){
	LOG(INFO) << "Actualizo listado de matchs (CandidateService - match).";
	this->userDao->putMatch(idUser, idUserMatch);
	return StatusCodeMatch::OK_UPDATE_MATCH;
}
