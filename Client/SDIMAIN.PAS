unit SDIMAIN;

interface

uses Windows, Classes, Graphics, Forms, Controls, Menus,
  Dialogs,ScktComp,Setupform, ExtCtrls, StdCtrls;

type
  TChatClient = class(TForm)
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    Panel1: TPanel;
    Panel2: TPanel;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    edt_username: TEdit;
    edt_Password: TEdit;
    btn_login: TButton;
    mmo_log: TMemo;
    Button1: TButton;
    Panel3: TPanel;
    Label3: TLabel;
    Label4: TLabel;
    lbl_tableNum: TLabel;
    lbl_ChairNum: TLabel;
    Button2: TButton;
    Label5: TLabel;
    lbl_UserState: TLabel;
    Panel4: TPanel;
    Panel5: TPanel;
    Panel6: TPanel;
    Panel7: TPanel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    procedure N2Click(Sender: TObject);
    procedure btn_loginClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    FSetupForm:TFrm_Setup;
    FClientSocket:TClientSocket;
    procedure OnClientRead(Sender: TObject; Socket: TCustomWinSocket); 
    { Private declarations }
  public
    { Public declarations }
  end;

var
  ChatClient: TChatClient;

implementation


{$R *.dfm}
uses
  Config,uProtocol,SysUtils;


procedure TChatClient.btn_loginClick(Sender: TObject);
//var
//  Msg:TDefaultMessage;
//  LoginMsg:TLoginMessage;
//  Buffer:Pointer;
//  Pos:integer;
begin
//  GetMem(Buffer,Sizeof(Msg)+Sizeof(TLoginMessage));
//  FillChar(LoginMsg,SizeOf(LoginMsg),#0);
//  Move(edt_username.Text[1],LoginMsg.name[0],Length(edt_username.text));
//  Move(edt_Password.Text[1],LoginMsg.Pass[0],Length(edt_Password.Text));
//  Msg.ID := 0 ;
//  Msg.Cmd := CM_Login;
//  Msg.Param:= 0 ;
//  Pos := 0;
//  Msg.BuffLen :=SizeOf(LoginMsg);
//  Move(msg,Buffer^,SizeOf(Msg));
//  Pos := Pos+Sizeof(Msg);
//  Move(LoginMsg,Pointer(Integer(Buffer)+Pos)^,SizeOf(TLoginMessage));
//  Pos := Pos+Sizeof(TLoginMessage);


//  FClientSocket.Socket.SendBuf(Buffer^,Pos);
end;



procedure TChatClient.Button1Click(Sender: TObject);
var
  Msg : TMessageDefault;
  MsgHead :TMessageHead;
  Buf:PChar;
  Tmpbuf:PChar;
  BufLen :integer;
  A:pMessageDefault;
begin
 //����λ
 BufLen :=0 ;
 BufLen := SizeOf(MsgHead)+sizeof(Msg);
 GetMem(Buf,SizeOf(MsgHead)+sizeof(Msg));
 FillChar(MsgHead,SizeOf(MsgHead),#0);
 MsgHead.Signed := $FF545454;
 MsgHead.CompressID := 0 ;
 MsgHead.BufferPos := SizeOf(MsgHead);
 MsgHead.BufferLen := SizeOf(Msg);
 FillChar(Msg,SizeOf(Msg),0);
 Msg.MessageID := CM_FIND_PLACE;
 CopyMemory(buf,@MsgHead,SizeOf(MsgHead));
 Tmpbuf := Buf + SizeOf(TMessageHead);
// Tmpbuf:=PChar(Buf+sizeof(MsgHead));
 CopyMemory(Tmpbuf,@Msg,SizeOf(Msg));
 FClientSocket.Socket.SendBuf(Buf^,BufLen);
 A := pMessageDefault(Tmpbuf);
 BufLen := A.RecogID;
 Caption := intTostr(buflen);



end;

procedure TChatClient.Button2Click(Sender: TObject);
 var
  Msg : TMessageDefault;
  MsgHead :TMessageHead;
  Buf:PChar;
  Tmpbuf:PChar;
  BufLen :integer;
  A:pMessageDefault;
begin
 //����λ
 BufLen :=0 ;
 BufLen := SizeOf(MsgHead)+sizeof(Msg);
 GetMem(Buf,SizeOf(MsgHead)+sizeof(Msg));
 FillChar(MsgHead,SizeOf(MsgHead),#0);
 MsgHead.Signed := $FF545454;
 MsgHead.CompressID := 0 ;
 MsgHead.BufferPos := SizeOf(MsgHead);
 MsgHead.BufferLen := SizeOf(Msg);
 FillChar(Msg,SizeOf(Msg),0);
 Msg.MessageID := CM_USER_READY;
 Msg.WParam := 1;
 CopyMemory(buf,@MsgHead,SizeOf(MsgHead));
 Tmpbuf := Buf + SizeOf(TMessageHead);
// Tmpbuf:=PChar(Buf+sizeof(MsgHead));
 CopyMemory(Tmpbuf,@Msg,SizeOf(Msg));
 FClientSocket.Socket.SendBuf(Buf^,BufLen);



end;

procedure TChatClient.N2Click(Sender: TObject);
begin
    FSetupForm := TFrm_Setup.Create(self);
    FSetupForm.ShowModal;
    FClientSocket := TClientSocket.Create(self);
    FClientSocket.Address := Get_Config().Address;
    FClientSocket.Port := Get_Config.Port;

    FClientSocket.OnRead:= OnClientRead;
    FClientSocket.Active := true;
end;

procedure TChatClient.OnClientRead(Sender: TObject; Socket: TCustomWinSocket);
var
  Buffer:array [0..4095] of AnsiChar;

  pBuf :pChar;
//  Msg :TDefaultMessage;
  DataLen:integer;
  Msg :pMessageHead;
  defaultmsg :pMessageDefault;
  Userinfo :TUserinfo;
  UI:pUserinfo;
  processLen:integer;
begin
  dataLen := 0 ;
  DataLen := Socket.ReceiveBuf(Buffer,4096);

  OutputDebugString(PAnsiChar(IntToStr(DataLen)));
  while DataLen > SizeOf(TMessageHead) do
  begin
       Msg := @Buffer[0];
       GetMem(pBuf,Msg.BufferLen);
       processLen := SizeOf(TMessageHead)+msg.BufferLen;
       CopyMemory(pBuf,PChar(Integer(msg)+sizeof(TMessageHead)),Msg.BufferLen);
       DataLen := DataLen- processLen;
       Move(Buffer[ProcessLen],Buffer[0],DataLen);
       if(Msg.Signed = $FF545454)then
       begin
         defaultmsg :=pMessageDefault(pBuf);
         case defaultmsg.MessageID of
            SM_FIND_PLACE:
            begin
             lbl_tableNum.Caption := intTostr(defaultmsg.WParam);
             lbl_ChairNum.Caption := inttostr(defaultmsg.LParam);
            end;
            SM_USER_READY:
            begin
             lbl_UserState.Caption := IntToStr(defaultmsg.WParam);
            end;
            SM_ADD_USER:
            begin
              UI := pUserInfo(Integer(defaultmsg) +sizeof(TMessageDefault));
              CopyMemory(@Userinfo,UI,SizeOf(defaultMsg.LParam));
             case defaultmsg.WParam  of
             0:
             begin
               Panel5.Caption := ui.name;
               if(ui.us = US_IDEL) then
                Label6.Caption := '����';
               if(ui.us =US_READY)then
                 Label6.Caption :='�ȴ�';
               
             end;
             1:
             begin
               Panel6.Caption := Ui.name;
               if(ui.us = US_IDEL) then
                Label7.Caption := '����';
               if(ui.us =US_READY)then
                 Label7.Caption :='�ȴ�';
             end;
             2:
             begin
               Panel7.Caption := UI.name;
               if(ui.us = US_IDEL) then
                Label8.Caption := '����';
               if(ui.us =US_READY)then
                 Label8.Caption :='�ȴ�';
             end;
             end;
            end;
         end;
        end;


  end;
//  if DataLen >= 16 then
//  begin
//   Move(Buffer,msg,SizeOf(TDefaultMessage));
//  end;
//  if (Msg.Cmd = SM_Login_OK) then
//  begin
//    //��½�ɹ�
////
//    mmo_log.Lines.add ('====Revice Message SM_Login_Ok====');
//  end;
end;

end.
