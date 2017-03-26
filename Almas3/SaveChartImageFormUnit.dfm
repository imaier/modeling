object SaveChartImageForm: TSaveChartImageForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1077#1080#1077' '#1075#1088#1072#1092#1080#1082#1072
  ClientHeight = 140
  ClientWidth = 444
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ChartLabel: TLabel
    Left = 8
    Top = 8
    Width = 38
    Height = 13
    Caption = #1043#1088#1072#1092#1080#1082
  end
  object ChartComboBox: TComboBox
    AlignWithMargins = True
    Left = 66
    Top = 5
    Width = 370
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
  end
  object BlackSeriesCheckBox: TCheckBox
    Left = 66
    Top = 32
    Width = 271
    Height = 17
    Caption = #1042#1089#1077' '#1082#1088#1080#1074#1099#1077' '#1095#1077#1088#1085#1086#1075#1086' '#1094#1074#1077#1090#1072
    Checked = True
    State = cbChecked
    TabOrder = 1
  end
  object RemoveLegendCheckBox: TCheckBox
    Left = 66
    Top = 55
    Width = 263
    Height = 17
    Caption = #1057#1082#1088#1099#1090#1100' '#1083#1077#1075#1077#1085#1076#1091
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object ButtonsPanel: TPanel
    Left = 0
    Top = 109
    Width = 444
    Height = 31
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 3
    object OkPanel: TPanel
      Left = 288
      Top = 0
      Width = 81
      Height = 31
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object OkButton: TButton
        Left = 0
        Top = 5
        Width = 75
        Height = 20
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        Default = True
        TabOrder = 0
        OnClick = OkButtonClick
      end
    end
    object CancelPanel: TPanel
      Left = 369
      Top = 0
      Width = 75
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
  object ChartSaveDialog: TSaveDialog
    DefaultExt = 'wmf'
    Filter = 'Windows media format|*.wmf|Bitmap file|*.bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 400
    Top = 72
  end
end
