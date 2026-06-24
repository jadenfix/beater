#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "archive_query_response.h"



static archive_query_response_t *archive_query_response_create_internal(
    list_t *rows
    ) {
    archive_query_response_t *archive_query_response_local_var = malloc(sizeof(archive_query_response_t));
    if (!archive_query_response_local_var) {
        return NULL;
    }
    archive_query_response_local_var->rows = rows;

    archive_query_response_local_var->_library_owned = 1;
    return archive_query_response_local_var;
}

__attribute__((deprecated)) archive_query_response_t *archive_query_response_create(
    list_t *rows
    ) {
    return archive_query_response_create_internal (
        rows
        );
}

void archive_query_response_free(archive_query_response_t *archive_query_response) {
    if(NULL == archive_query_response){
        return ;
    }
    if(archive_query_response->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "archive_query_response_free");
        return ;
    }
    listEntry_t *listEntry;
    if (archive_query_response->rows) {
        list_ForEach(listEntry, archive_query_response->rows) {
            archived_span_row_free(listEntry->data);
        }
        list_freeList(archive_query_response->rows);
        archive_query_response->rows = NULL;
    }
    free(archive_query_response);
}

cJSON *archive_query_response_convertToJSON(archive_query_response_t *archive_query_response) {
    cJSON *item = cJSON_CreateObject();

    // archive_query_response->rows
    if (!archive_query_response->rows) {
        goto fail;
    }
    cJSON *rows = cJSON_AddArrayToObject(item, "rows");
    if(rows == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *rowsListEntry;
    if (archive_query_response->rows) {
    list_ForEach(rowsListEntry, archive_query_response->rows) {
    cJSON *itemLocal = archived_span_row_convertToJSON(rowsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(rows, itemLocal);
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

archive_query_response_t *archive_query_response_parseFromJSON(cJSON *archive_query_responseJSON){

    archive_query_response_t *archive_query_response_local_var = NULL;

    // define the local list for archive_query_response->rows
    list_t *rowsList = NULL;

    // archive_query_response->rows
    cJSON *rows = cJSON_GetObjectItemCaseSensitive(archive_query_responseJSON, "rows");
    if (cJSON_IsNull(rows)) {
        rows = NULL;
    }
    if (!rows) {
        goto end;
    }

    
    cJSON *rows_local_nonprimitive = NULL;
    if(!cJSON_IsArray(rows)){
        goto end; //nonprimitive container
    }

    rowsList = list_createList();

    cJSON_ArrayForEach(rows_local_nonprimitive,rows )
    {
        if(!cJSON_IsObject(rows_local_nonprimitive)){
            goto end;
        }
        archived_span_row_t *rowsItem = archived_span_row_parseFromJSON(rows_local_nonprimitive);

        list_addElement(rowsList, rowsItem);
    }


    archive_query_response_local_var = archive_query_response_create_internal (
        rowsList
        );

    return archive_query_response_local_var;
end:
    if (rowsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, rowsList) {
            archived_span_row_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(rowsList);
        rowsList = NULL;
    }
    return NULL;

}
