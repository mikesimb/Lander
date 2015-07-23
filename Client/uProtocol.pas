unit uProtocol;

interface
uses
  Windows;
const
   //找座位
   CM_FIND_PLACE =  1002;
   //找到作为，WPARAM作为桌号，LPARAM作为座位号
   SM_FIND_PLACE = 1003;

type
  TMessageHead = record
    Signed:DWord;
    CompressID:DWORD;
    BufferPos:DWORD;
    BufferLen:DWord;
  end;
  TMessageDefault = record
    RecogID :DWORD;
    MessageID :DWORD;
    WParam:DWORD;
    LParam:DWORD;
  end;


implementation

end.
