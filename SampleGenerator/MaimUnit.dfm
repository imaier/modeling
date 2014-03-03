object MaimForm: TMaimForm
  Left = 398
  Top = 307
  Caption = #1043#1077#1085#1077#1088#1072#1090#1086#1088' '#1084#1086#1076#1077#1083#1077#1081
  ClientHeight = 140
  ClientWidth = 300
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object StatusLabel: TLabel
    Left = 8
    Top = 64
    Width = 281
    Height = 13
    Alignment = taCenter
    AutoSize = False
  end
  object GenerateButton: TButton
    Left = 56
    Top = 8
    Width = 177
    Height = 25
    Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103
    TabOrder = 0
    OnClick = GenerateButtonClick
  end
  object StopButton: TButton
    Left = 104
    Top = 80
    Width = 75
    Height = 25
    Caption = #1061#1074#1072#1090#1080#1090
    TabOrder = 1
    OnClick = StopButtonClick
  end
  object StatusProgressBar: TProgressBar
    Left = 8
    Top = 40
    Width = 281
    Height = 17
    TabOrder = 2
  end
  object SplitCheckBox: TCheckBox
    Left = 8
    Top = 107
    Width = 185
    Height = 17
    Caption = #1056#1072#1079#1073#1080#1090#1100' '#1085#1072' '#1075#1088#1091#1087#1087#1099' '#1087#1086' '#1090#1080#1087#1072#1084
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
  object CubeCheckBox: TCheckBox
    Left = 8
    Top = 123
    Width = 185
    Height = 17
    Caption = #1056#1072#1084#1082#1072' '#1074#1086#1082#1088#1091#1075
    Checked = True
    State = cbChecked
    TabOrder = 4
  end
end
