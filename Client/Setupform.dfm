object Frm_Setup: TFrm_Setup
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35774#32622
  ClientHeight = 147
  ClientWidth = 354
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 59
    Height = 13
    Caption = #26381#21153#22120' I P :'
  end
  object Label2: TLabel
    Left = 16
    Top = 56
    Width = 72
    Height = 13
    Caption = #26381#21153#22120#31471#21475#65306
  end
  object edt_Address: TEdit
    Left = 120
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object edt_Port: TEdit
    Left = 120
    Top = 51
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object btn_Ok: TButton
    Left = 232
    Top = 104
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 2
    OnClick = btn_OkClick
  end
end
