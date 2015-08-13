#include <string>
#include <stdio.h>
#include <functional>


class CZQCustomClient;
class CZQClientSocket;
typedef std::function<void()>  OnSocketNotifyEvent;
typedef std::function<void(CZQCustomClient * client)>  OnSocketConnectNotifyEvent;
typedef std::function<void(char * buf, int buflen)>  OnSocketReadNotifyEvent;
typedef std::function<void(char * buf, int buflen)>  OnSocketWriteNotifyEvent;
typedef std::function<CZQCustomClient * ()> OnCreateSocketClientNotifyEvent;

typedef std::function<void(TClientSocket*)> onClientSocketConnectNotifyEvent;
typedef std::function<void(TClientSocket*)> onClientSocketDisConnectNotifyEvent;
typedef std::function<void(TClientSocket*,int)> onClientErrorNotifyEvent;


#define CONFIG_FILE_NAME "LoginGate.ini"

std::string ExtractFilePath(std::string FullPathFileName);
bool FileExists(const char * strFilename);