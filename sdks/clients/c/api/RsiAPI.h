#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "../model/error_response.h"
#include "../model/gate_candidate_request.h"
#include "../model/gate_candidate_response.h"


gate_candidate_response_t*
RsiAPI_gateOptimizationCandidate(apiClient_t *apiClient, char *tenant_id, char *project_id, gate_candidate_request_t *gate_candidate_request, char *authorization, char *x_beater_api_key, char *x_beater_project_id, char *x_beater_environment_id);


