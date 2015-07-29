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
        Top = 82
        Width = 75
        Height = 25
        Caption = #30331#38470
        TabOrder = 2
        OnClick = btn_loginClick
      end
    end
    object Panel3: TPanel
      Left = 2
      Top = 137
      Width = 185
      Height = 331
      Align = alClient
      TabOrder = 1
      object Label3: TLabel
        Left = 15
        Top = 16
        Width = 48
        Height = 12
        Caption = #26700#23376#21495#65306
      end
      object Label4: TLabel
        Left = 15
        Top = 34
        Width = 48
        Height = 12
        Caption = #26885#23376#21495#65306
      end
      object lbl_tableNum: TLabel
        Left = 80
        Top = 16
        Width = 6
        Height = 12
      end
      object lbl_ChairNum: TLabel
        Left = 80
        Top = 34
        Width = 6
        Height = 12
      end
      object Label5: TLabel
        Left = 15
        Top = 52
        Width = 36
        Height = 12
        Caption = #29366#24577#65306
      end
      object lbl_UserState: TLabel
        Left = 57
        Top = 52
        Width = 24
        Height = 12
        Caption = #38386#32622
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
    object Button1: TButton
      Left = 6
      Top = 13
      Width = 75
      Height = 25
      Caption = #25214#24231#20301
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 104
      Top = 13
      Width = 75
      Height = 25
      Caption = #20934#22791
      TabOrder = 2
      OnClick = Button2Click
    end
    object Panel4: TPanel
      Left = 16
      Top = 58
      Width = 625
      Height = 303
      Caption = 'Panel4'
      TabOrder = 3
      object Panel5: TPanel
        Left = 24
        Top = 224
        Width = 81
        Height = 42
        Caption = 'Panel5'
        TabOrder = 0
        object Label6: TLabel
          Left = 37
          Top = 24
          Width = 36
          Height = 17
          Caption = 'Label6'
        end
      end
      object Panel6: TPanel
        Left = 264
        Top = 264
        Width = 73
        Height = 33
        Caption = 'Panel6'
        TabOrder = 1
        object Label7: TLabel
          Left = 37
          Top = 16
          Width = 36
          Height = 12
          Caption = 'Label6'
        end
      end
      object Panel7: TPanel
        Left = 528
        Top = 210
        Width = 73
        Height = 55
        Caption = 'Panel7'
        TabOrder = 2
        object Label8: TLabel
          Left = 29
          Top = 40
          Width = 36
          Height = 12
          Caption = 'Label6'
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 440
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
