/*
 * CandidateService.cpp
 *
 *  Created on: May 24, 2016
 *      Author: ediaz
 */

#include "CandidateService.h"

CandidateService::CandidateService(shared_ptr<DataBase> DB,shared_ptr<SharedClient> sharedClient) {
	this->sharedClient=sharedClient;
	shared_ptr<UserDao> userDaoAux(new UserDao(DB,sharedClient));
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

	//Actualizo cantidad diaria
	user = userDao->increaseQuantitySearchDaily(user);

	//Obtengo todos los usuarios cargados localmente
	candidates = userDao->getCandidatesForIdUser(idUser);

	LOG(DEBUG) << "Cantidad de candidatos inicial (CandidateService - searchCandidate): " << candidates.size();

	//Me quedo con el XX% menos votados
	candidates = getUsersLeastVoted(candidates);

	//Saco los que ya likeo en comun
	candidates = getUsersNotLiked(user, candidates);

	//Saco los que tuvieron un match en comun
	candidates = getUsersNotMatch(user, candidates);

	//Filtro por cercania. Me quedo con los que estan mas cerca
	candidates = getUsersNear(user, candidates);

	//Me quedo con los que tengan algun interes en comun
	candidates = getUsersCommonInterests(user, candidates);

	candidates = userDao->updateUserPhotoForUrl(candidates);

	search_candidate.change(OK_SEARCH, candidates);

	LOG(INFO) << "Fin de busqueda de candidatos a match (CandidateService - searchCandidate).";
	return search_candidate;
}

vector<User> CandidateService::getUsersNotLiked(User user, vector<User> candidates) {
	/*
	 * Saco a los que les dio like.
	 */
	LOG(DEBUG) << "Se van a sacar los candidatos a los que les dio like (CandidateService - getUsersNotLiked).";

	if(user.getIdUserCandidatesMatchs().empty()){
		LOG(DEBUG) << "Cantidad de candidatos a los que les dio like (CandidateService - getUsersNotLiked): 0";
		return candidates;
	}

	vector<User> candidatesOk;

	for(int i = 0; i < candidates.size(); i++){
		User candidate = candidates[i];
		bool like = false;
		int iMatch = 0;
		while (iMatch < user.getIdUserCandidatesMatchs().size() && !like){
			string idUserLike = user.getIdUserCandidatesMatchs()[iMatch];
			idUserLike = cleanString(idUserLike);
			if (idUserLike.compare(candidate.getId().c_str()) == 0){
				like = true;
				LOG(DEBUG) << "Candidato que se saca porque el usuario le dio like (CandidateService - getUsersNotLiked): " << idUserLike;
			}
			iMatch++;
		}

		if (!like){
			candidatesOk.push_back(candidate);
		}
	}

	LOG(DEBUG) << "Cantidad de candidatos a los que no le dio like  (CandidateService - getUsersNotLiked):" << candidatesOk.size();
	return candidatesOk;
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
	int quantity = round(div);

	LOG(DEBUG) << "Cantidad a sacar con mayor cantidad de matchs (CandidateService - getUsersLeastVoted):" << quantity;

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
	int i = (candidatesWithMatch.size() - 1);
	while (i >=0 && quantity > 0){
		quantity --;
		candidatesExclude.push_back(candidatesWithMatch[i]);
		LOG(DEBUG) << "Candidato que debo excluir por ser muy popular (CandidateService - getUsersLeastVoted): " << candidatesWithMatch[i].getId();
		i--;
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

	if(user.getIdUserMatchs().empty()){
		LOG(DEBUG) << "Cantidad de candidatos con los que no tuvo match (CandidateService - getUsersNotMatch): 0";
		return candidates;
	}

	vector<User> candidatesOk;

	for(int i = 0; i < candidates.size(); i++){
		User candidate = candidates[i];
		bool match = false;
		if (!candidate.getIdUserMatchs().empty()){
			int iMatch = 0;
			while (iMatch < candidate.getIdUserMatchs().size() && !match){
				string idUserMatch = candidate.getIdUserMatchs()[iMatch];
				idUserMatch = cleanString(idUserMatch);
				if (idUserMatch.compare(user.getId().c_str()) == 0){
					match = true;
					LOG(DEBUG) << "Candidato que se saca por tener ya un match con el usuario(CandidateService - getUsersNotMatch): " << idUserMatch;
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
			LOG(DEBUG) << "Este candidato se descarta por estar muy lejos (CandidateService - getUsersNear): " << candidate.getId();
			continue;
		}

		double distanceLongitude = fabs(fabs(user.getLongitude()) - fabs(candidate.getLongitude()));
		if (distanceLongitude > MAX_LONGITUDE){
			LOG(DEBUG) << "Este candidato se descarta por estar muy lejos (CandidateService - getUsersNear): " << candidate.getId();
			continue;
		}

		LOG(DEBUG) << "Este candidato esta cerca asi que se mantiene (CandidateService - getUsersNear): " << candidate.getId();
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
			LOG(DEBUG) << "Cantidad con el que se tiene algun interes en comun (CandidateService - getUsersCommonInterests): " << candidate.getId();
			candidatesOk.push_back(candidate);
		}
	}

	LOG(DEBUG) << "Cantidad de candidatos con los que tiene algun interes en comun (CandidateService - getUsersCommonInterests): " << candidatesOk.size();
	return candidatesOk;
}

StatusCodeMatch CandidateService::match(string idUser, string idUserMatch){
	LOG(INFO) << "Busco match entre el usuario " << idUser << " y el usuario " << idUserMatch << " (CandidateService - match).";

	User user = this->userDao->getUser(idUser);
	User candidate = this->userDao->getUser(idUserMatch);

	//Recorro los candidatos a match del candidato en busca de coincidencia
	bool find = false;
	int i = 0;
	while(i < candidate.getIdUserCandidatesMatchs().size() && !find){
		string idUserCandidateMatch = candidate.getIdUserCandidatesMatchs()[i];
		idUserCandidateMatch = cleanString(idUserCandidateMatch);
		if(user.getId().compare(idUserCandidateMatch) == 0){
			find = true;
		}
		i++;
	}

	if(!find){
		//Recorro que ya no sea un match
		i = 0;
		while(i < candidate.getIdUserMatchs().size() && !find){
			string idUserMatch = candidate.getIdUserMatchs()[i];
			idUserMatch = cleanString(idUserMatch);
			if(user.getId().compare(idUserMatch) == 0){
				find = true;
			}
			i++;
		}

		if (find){
			return StatusCodeMatch::ERROR_MATCH_DUPLICATE;
		}
	}

	if(find){
		LOG(INFO) << "Hubo match entre los usuarios.";
		bool putOk = this->userDao->putMatch(user, candidate);
		if (putOk){
			return StatusCodeMatch::OK_UPDATE_MATCH;
		}

		return StatusCodeMatch::ERROR_UPDATE_MATCH;
	} else {
		LOG(INFO) << "No hubo match entre los usuarios. Guardo el candidato.";
		bool putOk = this->userDao->putCandidateMatch(user, candidate);
		if (putOk){
			return StatusCodeMatch::OK_UPDATE_CANDIDATE_MATCH;
		}

		return StatusCodeMatch::ERROR_UPDATE_CANDIDATE_MATCH;
	}
}

string CandidateService::cleanString(string idUserCandidateMatch){
	/*
	 * Ejemplo de como viene:
	 * Name : idUserCandidateMatch
	 * Details:"\"RobertoM50.758326710562@gmail.com\"\n"
	 *
	 * Deberia de quedar:
	 * Details:"RobertoM50.758326710562@gmail.com"
	 */

	int length = idUserCandidateMatch.size() - 3;
	string idOk = idUserCandidateMatch.substr(1, length);

	return idOk;
}
