unit uProtocol;

interface
uses
  Windows;
const
   //����λ
   CM_FIND_PLACE =  1002;
   //�ҵ���Ϊ��WPARAM��Ϊ���ţ�LPARAM��Ϊ��λ��
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
