#include "messages.h"
#include "messagesList.h"

CMessages* CMessages::Create(int MesssageType) {
	switch (MesssageType) {
	case MESSAGE_LIST:
		return new CMessagesList();
	default:
		return new CMessagesList();
	}
	return NULL;
}