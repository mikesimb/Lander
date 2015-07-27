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
 //找座位
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
 //找座位
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
//  Msg :TDefaultMessage;
  DataLen:integer;
  Msg :pMessageHead;
  defaultmsg :pMessageDefault;
  Userinfo :TUserinfo;
  UI:pUserinfo;
begin
  dataLen := 0 ;
  DataLen := Socket.ReceiveBuf(Buffer,4096);
  Msg := @Buffer[0];
  if(Msg.Signed = $FF545454)then
  begin
     defaultmsg := pMessageDefault(Integer(Msg)+ msg.BufferPos);
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
          UI := pUserInfo(Integer(defaultmsg) +defaultmsg.LParam);
          CopyMemory(@Userinfo,UI,SizeOf(defaultMsg.LParam));
          if(defaultmsg.WParam = 1) then
          begin
            Panel5.Caption := UI.name;
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
//    //登陆成功
////
//    mmo_log.Lines.add ('====Revice Message SM_Login_Ok====');
//  end;
end;

end.
