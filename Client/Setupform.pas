unit Setupform;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TFrm_Setup = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    edt_Address: TEdit;
    edt_Port: TEdit;
    btn_Ok: TButton;
    procedure FormCreate(Sender: TObject);
    procedure btn_OkClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Frm_Setup: TFrm_Setup;

implementation

uses
  Config;

{$R *.dfm}

procedure TFrm_Setup.btn_OkClick(Sender: TObject);
var
  FileName:String;
begin
  Get_Config.Address:= edt_Address.Text;
  Get_Config.Port := StrToInt(edt_Port.text);
  FileName := ExtractFilePath(ParamStr(0));
  FileName := FileName +'User.ini';
  Get_Config.WriteConfig(FileName);
  Close;
end;

procedure TFrm_Setup.FormCreate(Sender: TObject);
var
  FileName:String;
begin
  FileName := ExtractFilePath(ParamStr(0));
  FileName := FileName +'User.ini';
  Get_Config.LoadConfig(FileName);
  edt_Address.Text := Get_Config.Address;
  edt_Port.Text := IntToStr(Get_Config.Port);
  
end;

end.
