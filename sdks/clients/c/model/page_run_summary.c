#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "page_run_summary.h"



static page_run_summary_t *page_run_summary_create_internal(
    list_t *items,
    char *next_cursor
    ) {
    page_run_summary_t *page_run_summary_local_var = malloc(sizeof(page_run_summary_t));
    if (!page_run_summary_local_var) {
        return NULL;
    }
    page_run_summary_local_var->items = items;
    page_run_summary_local_var->next_cursor = next_cursor;

    page_run_summary_local_var->_library_owned = 1;
    return page_run_summary_local_var;
}

__attribute__((deprecated)) page_run_summary_t *page_run_summary_create(
    list_t *items,
    char *next_cursor
    ) {
    return page_run_summary_create_internal (
        items,
        next_cursor
        );
}

void page_run_summary_free(page_run_summary_t *page_run_summary) {
    if(NULL == page_run_summary){
        return ;
    }
    if(page_run_summary->_library_owned != 1){
        fprintf(stderr, "WARNING: %s() does NOT free objects allocated by the user\n", "page_run_summary_free");
        return ;
    }
    listEntry_t *listEntry;
    if (page_run_summary->items) {
        list_ForEach(listEntry, page_run_summary->items) {
            page_run_summary_items_inner_free(listEntry->data);
        }
        list_freeList(page_run_summary->items);
        page_run_summary->items = NULL;
    }
    if (page_run_summary->next_cursor) {
        free(page_run_summary->next_cursor);
        page_run_summary->next_cursor = NULL;
    }
    free(page_run_summary);
}

cJSON *page_run_summary_convertToJSON(page_run_summary_t *page_run_summary) {
    cJSON *item = cJSON_CreateObject();

    // page_run_summary->items
    if (!page_run_summary->items) {
        goto fail;
    }
    cJSON *items = cJSON_AddArrayToObject(item, "items");
    if(items == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *itemsListEntry;
    if (page_run_summary->items) {
    list_ForEach(itemsListEntry, page_run_summary->items) {
    cJSON *itemLocal = page_run_summary_items_inner_convertToJSON(itemsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(items, itemLocal);
    }
    }


    // page_run_summary->next_cursor
    if(page_run_summary->next_cursor) {
    if(cJSON_AddStringToObject(item, "next_cursor", page_run_summary->next_cursor) == NULL) {
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

page_run_summary_t *page_run_summary_parseFromJSON(cJSON *page_run_summaryJSON){

    page_run_summary_t *page_run_summary_local_var = NULL;

    // define the local list for page_run_summary->items
    list_t *itemsList = NULL;

    // page_run_summary->items
    cJSON *items = cJSON_GetObjectItemCaseSensitive(page_run_summaryJSON, "items");
    if (cJSON_IsNull(items)) {
        items = NULL;
    }
    if (!items) {
        goto end;
    }

    
    cJSON *items_local_nonprimitive = NULL;
    if(!cJSON_IsArray(items)){
        goto end; //nonprimitive container
    }

    itemsList = list_createList();

    cJSON_ArrayForEach(items_local_nonprimitive,items )
    {
        if(!cJSON_IsObject(items_local_nonprimitive)){
            goto end;
        }
        page_run_summary_items_inner_t *itemsItem = page_run_summary_items_inner_parseFromJSON(items_local_nonprimitive);

        list_addElement(itemsList, itemsItem);
    }

    // page_run_summary->next_cursor
    cJSON *next_cursor = cJSON_GetObjectItemCaseSensitive(page_run_summaryJSON, "next_cursor");
    if (cJSON_IsNull(next_cursor)) {
        next_cursor = NULL;
    }
    if (next_cursor) { 
    if(!cJSON_IsString(next_cursor) && !cJSON_IsNull(next_cursor))
    {
    goto end; //String
    }
    }


    page_run_summary_local_var = page_run_summary_create_internal (
        itemsList,
        next_cursor && !cJSON_IsNull(next_cursor) ? strdup(next_cursor->valuestring) : NULL
        );

    return page_run_summary_local_var;
end:
    if (itemsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, itemsList) {
            page_run_summary_items_inner_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(itemsList);
        itemsList = NULL;
    }
    return NULL;

}
