unit Config;

interface
uses
  IniFiles,SysUtils;

type
  TConfig = class
    private
      FIni:TIniFile;
      FAddress:string;
      FPort:integer;

    protected

    public
      constructor Create;
      destructor Destroy;override;
      procedure  LoadConfig(FileName:string);
      procedure WriteConfig(FileName:string);
      Property Address:string read FAddress write FAddress;
      property Port :Integer read FPort write FPort;
      

  end;
  function Get_Config():TConfig;
implementation
var
  g_Config:TConfig;

{ TConfig }

function Get_Config():TConfig;
begin
  if not Assigned(g_Config) then
  begin
     g_Config := TConfig.Create;

  end;
  Result := g_Config;
end;

constructor TConfig.Create;
begin
  FAddress := '';
  FPort := 0;
end;

destructor TConfig.Destroy;
begin

  inherited;
end;

procedure TConfig.LoadConfig(FileName: string);
begin
  FIni := TIniFile.Create(FileName);
  FAddress := FIni.ReadString('Setup','Address','');
  FPort := FIni.ReadInteger('Setup','Port',0);
  FreeAndnil(FIni);
end;

procedure TConfig.WriteConfig(FileName: string);
begin
    FIni := TIniFile.Create(FileName);
    FIni.WriteString('Setup','Address',FAddress);
    FIni.WriteInteger('Setup','Port',FPort);
    FreeAndnil(FIni);
end;

initialization

finalization
  if Assigned(g_Config) then
  begin
    FreeAndNil(g_Config);
  end;

end.
