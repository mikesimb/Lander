object ChatClient: TChatClient
  Left = 197
  Top = 111
  Caption = 'Chat'
  ClientHeight = 474
  ClientWidth = 847
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #23435#20307
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 193
    Height = 474
    Align = alLeft
    Alignment = taLeftJustify
    BevelInner = bvLowered
    BevelKind = bkSoft
    BevelOuter = bvLowered
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 2
      Top = 2
      Width = 185
      Height = 135
      Align = alTop
      Caption = #30331#38470#21306#22495
      TabOrder = 0
      object Label1: TLabel
        Left = 3
        Top = 24
        Width = 48
        Height = 12
        Caption = #29992#25143#21517#65306
      end
      object Label2: TLabel
        Left = 3
        Top = 59
        Width = 48
        Height = 12
        Caption = #23494'  '#30721#65306
      end
      object edt_username: TEdit
        Left = 48
        Top = 21
        Width = 121
        Height = 20
        TabOrder = 0
      end
      object edt_Password: TEdit
        Left = 48
        Top = 56
        Width = 121
        Height = 20
        TabOrder = 1
      end
      object btn_login: TButton
        Left = 94
        Top = 96
        Width = 75
        Height = 25
        Caption = #30331#38470
        TabOrder = 2
        OnClick = btn_loginClick
      end
    end
  end
  object Panel2: TPanel
    Left = 193
    Top = 0
    Width = 654
    Height = 474
    Align = alClient
    BevelInner = bvLowered
    BevelKind = bkSoft
    BevelOuter = bvLowered
    TabOrder = 1
    object mmo_log: TMemo
      Left = 2
      Top = 379
      Width = 646
      Height = 89
      Align = alBottom
      Lines.Strings = (
        'mmo_log')
      TabOrder = 0
    end
  end
  object MainMenu1: TMainMenu
    Left = 96
    Top = 248
    object N1: TMenuItem
      Caption = #35774#32622
      object N2: TMenuItem
        Caption = #32593#32476#35774#32622
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #30331#38470#35774#32622
      end
    end
  end
end
