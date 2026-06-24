#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "run_gate_request.h"



static run_gate_request_t *run_gate_request_create_internal(
    char *experiment_run_id
    ) {
    run_gate_request_t *run_gate_request_local_var = malloc(sizeof(run_gate_request_t));
    if (!run_gate_request_local_var) {
        return NULL;
    }
    run_gate_request_local_var->experiment_run_id = experiment_run_id;

    run_gate_request_local_var->_library_owned = 1;
    return run_gate_request_local_var;
}

__attribute__((deprecated)) run_gate_request_t *run_gate_request_create(
    char *experiment_run_id
    ) {
    return run_gate_request_create_internal (
        experiment_run_id
        );
}

void run_gate_request_free(run_gate_request_t *run_gate_request) {
    if(NULL == run_gate_request){
        return ;
    }
    if(run_gate_request->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "run_gate_request_free");
        return ;
    }
    listEntry_t *listEntry;
    if (run_gate_request->experiment_run_id) {
        free(run_gate_request->experiment_run_id);
        run_gate_request->experiment_run_id = NULL;
    }
    free(run_gate_request);
}

cJSON *run_gate_request_convertToJSON(run_gate_request_t *run_gate_request) {
    cJSON *item = cJSON_CreateObject();

    // run_gate_request->experiment_run_id
    if(run_gate_request->experiment_run_id) {
    if(cJSON_AddStringToObject(item, "experiment_run_id", run_gate_request->experiment_run_id) == NULL) {
    goto fail; //String
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

run_gate_request_t *run_gate_request_parseFromJSON(cJSON *run_gate_requestJSON){

    run_gate_request_t *run_gate_request_local_var = NULL;

    // run_gate_request->experiment_run_id
    cJSON *experiment_run_id = cJSON_GetObjectItemCaseSensitive(run_gate_requestJSON, "experiment_run_id");
    if (cJSON_IsNull(experiment_run_id)) {
        experiment_run_id = NULL;
    }
    if (experiment_run_id) { 
    if(!cJSON_IsString(experiment_run_id) && !cJSON_IsNull(experiment_run_id))
    {
    goto end; //String
    }
    }


    run_gate_request_local_var = run_gate_request_create_internal (
        experiment_run_id && !cJSON_IsNull(experiment_run_id) ? strdup(experiment_run_id->valuestring) : NULL
        );

    return run_gate_request_local_var;
end:
    return NULL;

}
