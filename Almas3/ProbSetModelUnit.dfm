object ProbSetModelForm: TProbSetModelForm
  Left = 70
  Top = 304
  BorderIcons = [biSystemMenu]
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099
  ClientHeight = 250
  ClientWidth = 425
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
  object ButtonsPanel: TPanel
    Left = 0
    Top = 219
    Width = 425
    Height = 31
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitTop = 182
    object OkPanel: TPanel
      Left = 292
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
        ModalResult = 1
        TabOrder = 0
        OnClick = OkButtonClick
      end
    end
    object CancelPanel: TPanel
      Left = 360
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
  object ClientPanel: TPanel
    Left = 0
    Top = 0
    Width = 425
    Height = 219
    Align = alClient
    BevelOuter = bvNone
    BorderWidth = 5
    Caption = 'ClientPanel'
    TabOrder = 1
    ExplicitHeight = 182
    object Splitter1: TSplitter
      Left = 5
      Top = 155
      Width = 415
      Height = 3
      Cursor = crVSplit
      Align = alTop
      Beveled = True
      ExplicitTop = 97
      ExplicitWidth = 253
    end
    object SufModelRadioGroup: TRadioGroup
      Left = 5
      Top = 5
      Width = 415
      Height = 150
      Align = alTop
      Caption = ' '#1052#1086#1076#1077#1083#1100' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1080' '
      TabOrder = 0
      TabStop = True
      OnClick = SufModelRadioGroupClick
    end
    object InfoPanel: TPanel
      Left = 5
      Top = 158
      Width = 415
      Height = 56
      Align = alClient
      BevelOuter = bvNone
      BorderWidth = 5
      TabOrder = 1
      ExplicitTop = 116
      ExplicitHeight = 61
      object InfoLabel: TLabel
        Left = 5
        Top = 5
        Width = 405
        Height = 46
        Align = alClient
        Caption = #1054#1087#1080#1089#1072#1085#1080#1077
        WordWrap = True
        ExplicitWidth = 50
        ExplicitHeight = 13
      end
    end
  end
end
