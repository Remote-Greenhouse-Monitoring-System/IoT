
#include "Initialize.h"

EventGroupHandle_t measureEventGroup;
EventGroupHandle_t dataReadyEventGroup;


void initialize_event_groups() 
{
	measureEventGroup = xEventGroupCreate();
	dataReadyEventGroup = xEventGroupCreate();
}
