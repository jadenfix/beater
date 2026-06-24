#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "search_response.h"



static search_response_t *search_response_create_internal(
    list_t *hits
    ) {
    search_response_t *search_response_local_var = malloc(sizeof(search_response_t));
    if (!search_response_local_var) {
        return NULL;
    }
    search_response_local_var->hits = hits;

    search_response_local_var->_library_owned = 1;
    return search_response_local_var;
}

__attribute__((deprecated)) search_response_t *search_response_create(
    list_t *hits
    ) {
    return search_response_create_internal (
        hits
        );
}

void search_response_free(search_response_t *search_response) {
    if(NULL == search_response){
        return ;
    }
    if(search_response->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "search_response_free");
        return ;
    }
    listEntry_t *listEntry;
    if (search_response->hits) {
        list_ForEach(listEntry, search_response->hits) {
            search_hit_free(listEntry->data);
        }
        list_freeList(search_response->hits);
        search_response->hits = NULL;
    }
    free(search_response);
}

cJSON *search_response_convertToJSON(search_response_t *search_response) {
    cJSON *item = cJSON_CreateObject();

    // search_response->hits
    if (!search_response->hits) {
        goto fail;
    }
    cJSON *hits = cJSON_AddArrayToObject(item, "hits");
    if(hits == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *hitsListEntry;
    if (search_response->hits) {
    list_ForEach(hitsListEntry, search_response->hits) {
    cJSON *itemLocal = search_hit_convertToJSON(hitsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(hits, itemLocal);
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

search_response_t *search_response_parseFromJSON(cJSON *search_responseJSON){

    search_response_t *search_response_local_var = NULL;

    // define the local list for search_response->hits
    list_t *hitsList = NULL;

    // search_response->hits
    cJSON *hits = cJSON_GetObjectItemCaseSensitive(search_responseJSON, "hits");
    if (cJSON_IsNull(hits)) {
        hits = NULL;
    }
    if (!hits) {
        goto end;
    }

    
    cJSON *hits_local_nonprimitive = NULL;
    if(!cJSON_IsArray(hits)){
        goto end; //nonprimitive container
    }

    hitsList = list_createList();

    cJSON_ArrayForEach(hits_local_nonprimitive,hits )
    {
        if(!cJSON_IsObject(hits_local_nonprimitive)){
            goto end;
        }
        search_hit_t *hitsItem = search_hit_parseFromJSON(hits_local_nonprimitive);

        list_addElement(hitsList, hitsItem);
    }


    search_response_local_var = search_response_create_internal (
        hitsList
        );

    return search_response_local_var;
end:
    if (hitsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, hitsList) {
            search_hit_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(hitsList);
        hitsList = NULL;
    }
    return NULL;

}
