unit uProtocol;

interface
uses
  Windows;
const
   //找座位
   CM_FIND_PLACE =  1002;
   //找到作为，WPARAM作为桌号，LPARAM作为座位号
   SM_FIND_PLACE = 1003;

   CM_USER_READY = 1004;//玩家准备好了

   SM_User_READY = 1005;//同步玩家的状态

type
  pMessageHead = ^TMessageHead;
  TMessageHead = packed record
    Signed:DWord;
    CompressID:DWORD;
    BufferPos:DWORD;
    BufferLen:DWord;
  end;
  pMessageDefault = ^TMessageDefault;
  TMessageDefault = packed record 
    RecogID :DWORD;
    MessageID :DWORD;
    WParam:DWORD;
    LParam:DWORD;
  end;


implementation

end.
