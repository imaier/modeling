object MaimForm: TMaimForm
  Left = 398
  Top = 307
  Caption = #1043#1077#1085#1077#1088#1072#1090#1086#1088' '#1084#1086#1076#1077#1083#1077#1081
  ClientHeight = 238
  ClientWidth = 409
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
    Top = 152
    Width = 386
    Height = 13
    Alignment = taCenter
    AutoSize = False
  end
  object GenerateButton: TButton
    Left = 112
    Top = 96
    Width = 177
    Height = 25
    Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103
    TabOrder = 0
    OnClick = GenerateButtonClick
  end
  object StopButton: TButton
    Left = 163
    Top = 168
    Width = 75
    Height = 25
    Caption = #1061#1074#1072#1090#1080#1090
    TabOrder = 1
    OnClick = StopButtonClick
  end
  object StatusProgressBar: TProgressBar
    Left = 8
    Top = 127
    Width = 385
    Height = 17
    TabOrder = 2
  end
  object SplitCheckBox: TCheckBox
    Left = 8
    Top = 195
    Width = 185
    Height = 17
    Caption = #1056#1072#1079#1073#1080#1090#1100' '#1085#1072' '#1075#1088#1091#1087#1087#1099' '#1087#1086' '#1090#1080#1087#1072#1084
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
  object CubeCheckBox: TCheckBox
    Left = 8
    Top = 211
    Width = 185
    Height = 17
    Caption = #1056#1072#1084#1082#1072' '#1074#1086#1082#1088#1091#1075
    Checked = True
    State = cbChecked
    TabOrder = 4
  end
  object ProbSetRadioGroup: TRadioGroup
    Left = 0
    Top = -1
    Width = 409
    Height = 91
    Caption = ' '#1053#1072#1073#1086#1088' '#1074#1077#1088#1086#1103#1090#1085#1086#1089#1090#1077#1081' '
    ItemIndex = 0
    Items.Strings = (
      #1054#1073#1098#1077#1084#1085#1086'-'#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1077' ('#1087#1088#1103#1084#1099#1077' '#1080' '#1085#1077' '#1087#1088#1103#1084#1099#1077')'
      #1054#1073#1098#1077#1084#1085#1086'-'#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1077' ('#1073#1077#1079' '#1086#1073#1098#1077#1084#1085#1099#1093' '#1074#1090#1086#1088#1099#1093' '#1089#1086#1089#1089#1077#1076#1077#1081')'
      
        #1054#1073#1098#1077#1084#1085#1086'-'#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1077' ('#1073#1077#1079' '#1087#1088#1103#1084#1099#1093' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1074#1090#1086#1088#1099#1093' '#1089#1086#1089#1089#1077#1076#1077#1081')' +
        '"'
      #1055#1077#1088#1074#1099#1077' '#1080' '#1074#1090#1086#1088#1099#1077' '#1087#1088#1103#1084#1099#1077', '#1074#1090#1086#1088#1099#1077' '#1085#1077#1087#1088#1103#1084#1099#1077' '#1089#1086#1089#1077#1076#1080)
    TabOrder = 5
  end
end
