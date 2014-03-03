object ScreenCopyForm: TScreenCopyForm
  Left = 344
  Top = 150
  BorderStyle = bsSingle
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1082#1072#1076#1088#1072
  ClientHeight = 451
  ClientWidth = 242
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object HeightLabel: TLabel
    Left = 53
    Top = 48
    Width = 41
    Height = 13
    Caption = #1042#1099#1089#1086#1090#1072':'
  end
  object WidthLabel: TLabel
    Left = 52
    Top = 20
    Width = 42
    Height = 13
    Caption = #1064#1080#1088#1080#1085#1072':'
  end
  object QualityLabel: TLabel
    Left = 4
    Top = 112
    Width = 90
    Height = 13
    Alignment = taRightJustify
    Caption = #1050#1072#1095#1077#1089#1090#1074#1086' '#1072#1090#1086#1084#1086#1074':'
  end
  object ButtonsPanel: TPanel
    Left = 0
    Top = 420
    Width = 242
    Height = 31
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 4
    object OkPanel: TPanel
      Left = 109
      Top = 0
      Width = 68
      Height = 31
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object OkButton: TButton
        Left = 2
        Top = 5
        Width = 61
        Height = 20
        Caption = 'Ok'
        Default = True
        TabOrder = 0
        OnClick = OkButtonClick
      end
    end
    object CancelPanel: TPanel
      Left = 177
      Top = 0
      Width = 65
      Height = 31
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 1
      object CancelButton: TButton
        Left = 2
        Top = 5
        Width = 61
        Height = 20
        Cancel = True
        Caption = #1054#1090#1084#1077#1085#1072
        ModalResult = 2
        TabOrder = 0
      end
    end
  end
  object HeightEdit: TEdit
    Left = 96
    Top = 44
    Width = 121
    Height = 21
    TabOrder = 1
    OnChange = HeightEditChange
  end
  object RatioCheckBox: TCheckBox
    Left = 16
    Top = 80
    Width = 209
    Height = 17
    Caption = #1054#1090#1085#1086#1096#1077#1085#1080#1077' '#1089#1090#1086#1088#1086#1085' '#1082#1072#1082' '#1091' '#1086#1088#1080#1075#1080#1085#1072#1083#1072
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object WidthEdit: TEdit
    Left = 96
    Top = 16
    Width = 121
    Height = 21
    TabOrder = 0
    OnChange = WidthEditChange
  end
  object QualityEdit: TEdit
    Left = 96
    Top = 108
    Width = 121
    Height = 21
    TabOrder = 3
    Text = '30'
  end
  object PintIndexCheckBox: TCheckBox
    Left = 16
    Top = 136
    Width = 209
    Height = 17
    Hint = #1054#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077' '#1080#1085#1076#1077#1082#1089#1086#1074' '#1052#1080#1083#1083#1077#1088#1072' '#1074' '#1083#1077#1074#1086#1084' '#1085#1080#1078#1085#1077#1084' '#1091#1075#1083#1091' '#1089#1082#1088#1080#1085#1096#1086#1090#1072
    Caption = #1042#1099#1074#1077#1089#1090#1080' '#1080#1085#1076#1077#1082#1089#1099' '#1052#1080#1083#1083#1077#1088#1072
    Checked = True
    ParentShowHint = False
    ShowHint = True
    State = cbChecked
    TabOrder = 5
  end
  object CaptureCheckBox: TCheckBox
    Left = 16
    Top = 160
    Width = 161
    Height = 17
    Caption = #1047#1072#1087#1080#1089#1100' '#1074#1080#1076#1077#1086#1088#1103#1076#1072
    TabOrder = 6
    OnClick = CaptureCheckBoxClick
  end
  object CaptureGroupBox: TGroupBox
    Left = 8
    Top = 184
    Width = 225
    Height = 233
    Caption = ' '#1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1074#1080#1076#1077#1086#1088#1103#1076#1072' '
    TabOrder = 7
    object BaseNameLabel: TLabel
      Left = 13
      Top = 152
      Width = 69
      Height = 26
      Caption = #1041#1072#1079#1086#1074#1086#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072
      WordWrap = True
    end
    object DirLabel: TLabel
      Left = 13
      Top = 184
      Width = 109
      Height = 13
      Caption = #1050#1072#1090#1072#1083#1086#1075' '#1085#1072#1079#1072#1085#1072#1095#1077#1085#1080#1103
      WordWrap = True
    end
    object DelAtomGroupBox: TGroupBox
      Left = 8
      Top = 16
      Width = 209
      Height = 105
      Caption = ' '#1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1091#1076#1072#1083#1103#1077#1084#1099#1093' '#1072#1090#1086#1084#1086#1074' '
      TabOrder = 0
      object FromLabel: TLabel
        Left = 4
        Top = 24
        Width = 79
        Height = 13
        Caption = #1055#1077#1088#1077#1076' '#1079#1072#1087#1080#1089#1100#1102
      end
      object StepLabel: TLabel
        Left = 63
        Top = 52
        Width = 20
        Height = 13
        Caption = #1064#1072#1075
      end
      object ToLabel: TLabel
        Left = 68
        Top = 79
        Width = 15
        Height = 13
        Caption = #1044#1086
      end
      object FromEdit: TEdit
        Left = 88
        Top = 20
        Width = 113
        Height = 21
        TabOrder = 0
        Text = '0'
        OnChange = WidthEditChange
      end
      object StepEdit: TEdit
        Left = 88
        Top = 48
        Width = 113
        Height = 21
        TabOrder = 1
        Text = '1'
        OnChange = HeightEditChange
      end
      object ToEdit: TEdit
        Left = 88
        Top = 75
        Width = 113
        Height = 21
        TabOrder = 2
        Text = '100'
        OnChange = HeightEditChange
      end
    end
    object BaseNameEdit: TEdit
      Left = 96
      Top = 156
      Width = 121
      Height = 21
      TabOrder = 1
      OnChange = HeightEditChange
    end
    object DirButton: TButton
      Left = 200
      Top = 200
      Width = 19
      Height = 20
      Caption = '...'
      TabOrder = 2
      OnClick = DirButtonClick
    end
    object DirEdit: TEdit
      Left = 8
      Top = 200
      Width = 185
      Height = 21
      TabOrder = 3
    end
    object SeveralOrnCheckBox: TCheckBox
      Left = 8
      Top = 129
      Width = 209
      Height = 17
      Hint = 
        #1053#1091#1078#1085#1099#1077' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1080' '#1076#1086#1083#1078#1085#1099' '#1073#1099#1090#1100' '#1087#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1086' '#1079#1072#1085#1077#1089#1077#1085#1099' '#1074' '#1089#1087#1080#1089#1086#1082' '#1086 +
        #1088#1080#1077#1090#1072#1094#1080#1081', '#1072' '#1083#1080#1096#1085#1080#1077' - '#1091#1076#1072#1083#1077#1085#1099
      Caption = #1057#1085#1080#1084#1082#1080' '#1074' '#1088#1072#1079#1085#1099#1093' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1103#1093
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
    end
  end
end
