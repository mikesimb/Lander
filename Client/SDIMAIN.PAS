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
    procedure N2Click(Sender: TObject);
    procedure btn_loginClick(Sender: TObject);
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
  Config;


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
begin
  dataLen := 0 ;
  DataLen := Socket.ReceiveBuf(Buffer,4096);
  if(DataLen >0) then
  begin
      OutputDebugString(Buffer);
  end;
//  if DataLen >= 16 then
//  begin
//   Move(Buffer,msg,SizeOf(TDefaultMessage));
//  end;
//  if (Msg.Cmd = SM_Login_OK) then
//  begin
//    //µÇÂ½³É¹¦
////
//    mmo_log.Lines.add ('====Revice Message SM_Login_Ok====');
//  end;
end;

end.
