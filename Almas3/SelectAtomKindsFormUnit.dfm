object SelectAtomKindsForm: TSelectAtomKindsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1086#1088' '#1090#1080#1087#1086#1074' '#1072#1090#1086#1084#1086#1074' '#1087#1086' '#1086#1089#1103#1084
  ClientHeight = 117
  ClientWidth = 337
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object YLabel: TLabel
    Left = 8
    Top = 19
    Width = 65
    Height = 13
    Caption = #1054#1089#1100' '#1086#1088#1076#1080#1085#1072#1090
  end
  object XLabel: TLabel
    Left = 8
    Top = 54
    Width = 61
    Height = 13
    Caption = #1054#1089#1100' '#1072#1073#1089#1094#1080#1089#1089
  end
  object YComboBox: TComboBox
    Left = 96
    Top = 16
    Width = 233
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
  end
  object XComboBox: TComboBox
    Left = 96
    Top = 51
    Width = 233
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
  end
  object ButtonsPanel: TPanel
    Left = 0
    Top = 86
    Width = 337
    Height = 31
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    object OkPanel: TPanel
      Left = 204
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
      Left = 272
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
end
