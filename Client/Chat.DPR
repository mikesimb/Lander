program Chat;

uses
  Forms,
  SDIMAIN in 'SDIMAIN.pas' {ChatClient},
  Config in 'Config.pas',
  Setupform in 'Setupform.pas' {Frm_Setup};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TChatClient, ChatClient);
  Application.CreateForm(TFrm_Setup, Frm_Setup);
  Application.Run;
end.
 
