object MillersForm: TMillersForm
  Left = 273
  Top = 176
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1055#1088#1086#1080#1079#1074#1086#1083#1100#1085#1099#1077' '#1080#1085#1076#1077#1082#1089#1099
  ClientHeight = 251
  ClientWidth = 234
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
    Top = 220
    Width = 234
    Height = 31
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object OkPanel: TPanel
      Left = 101
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
      Left = 169
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 4
    Width = 217
    Height = 57
    Caption = ' '#1048#1085#1076#1077#1082#1089#1099' '
    TabOrder = 1
    object DirectIndexHLabel: TLabel
      Left = 13
      Top = 21
      Width = 6
      Height = 13
      Caption = 'h'
    end
    object DirectIndexKLabel: TLabel
      Left = 79
      Top = 21
      Width = 6
      Height = 13
      Caption = 'k'
    end
    object DirectIndexLLabel: TLabel
      Left = 146
      Top = 21
      Width = 2
      Height = 13
      Caption = 'l'
    end
    object DirectIndexHEdit: TEdit
      Left = 22
      Top = 17
      Width = 41
      Height = 21
      TabOrder = 0
      Text = '1'
      OnChange = DirectIndexHEditChange
      OnEnter = DirectIndexHEditChange
    end
    object DirectIndexKEdit: TEdit
      Left = 89
      Top = 17
      Width = 41
      Height = 21
      TabOrder = 1
      Text = '0'
      OnChange = DirectIndexHEditChange
      OnEnter = DirectIndexHEditChange
    end
    object DirectIndexLEdit: TEdit
      Left = 156
      Top = 17
      Width = 41
      Height = 21
      TabOrder = 2
      Text = '0'
      OnChange = DirectIndexHEditChange
      OnEnter = DirectIndexHEditChange
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 68
    Width = 217
    Height = 57
    Caption = ' '#1055#1077#1088#1087#1077#1085#1076#1080#1082#1091#1083#1103#1088#1085#1099#1077' '#1080#1085#1076#1077#1082#1089#1099' '
    TabOrder = 2
    object PerpIndexHLabel: TLabel
      Left = 13
      Top = 21
      Width = 6
      Height = 13
      Caption = 'h'
    end
    object PerpIndexKLabel: TLabel
      Left = 79
      Top = 21
      Width = 6
      Height = 13
      Caption = 'k'
    end
    object PerpIndexLLabel: TLabel
      Left = 146
      Top = 21
      Width = 2
      Height = 13
      Caption = 'l'
    end
    object PerpIndexHEdit: TEdit
      Left = 22
      Top = 17
      Width = 41
      Height = 21
      ReadOnly = True
      TabOrder = 0
      OnEnter = DirectIndexHEditChange
    end
    object PerpIndexKEdit: TEdit
      Left = 89
      Top = 17
      Width = 41
      Height = 21
      ReadOnly = True
      TabOrder = 1
      OnEnter = DirectIndexHEditChange
    end
    object PerpIndexLEdit: TEdit
      Left = 156
      Top = 17
      Width = 41
      Height = 21
      ReadOnly = True
      TabOrder = 2
      OnEnter = DirectIndexHEditChange
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 132
    Width = 217
    Height = 77
    Caption = #1059#1075#1086#1083' '#1084#1077#1078#1076#1091' '#1087#1083#1086#1089#1082#1086#1089#1090#1103#1084#1080
    TabOrder = 3
    object AngleIndexHLabel: TLabel
      Left = 13
      Top = 21
      Width = 6
      Height = 13
      Caption = 'h'
    end
    object AngleIndexKLabel: TLabel
      Left = 79
      Top = 21
      Width = 6
      Height = 13
      Caption = 'k'
    end
    object AngleIndexLLabel: TLabel
      Left = 146
      Top = 21
      Width = 2
      Height = 13
      Caption = 'l'
    end
    object AngleLabel: TLabel
      Left = 24
      Top = 48
      Width = 60
      Height = 13
      Caption = #1059#1075#1086#1083' ('#1075#1088#1072#1076'):'
    end
    object AngleValueLabel: TLabel
      Left = 88
      Top = 48
      Width = 47
      Height = 13
      Caption = #1079#1085#1072#1095#1077#1085#1080#1077
    end
    object AngleIndexHEdit: TEdit
      Left = 22
      Top = 17
      Width = 41
      Height = 21
      TabOrder = 0
      Text = '1'
      OnChange = DirectIndexHEditChange
      OnEnter = DirectIndexHEditChange
    end
    object AngleIndexKEdit: TEdit
      Left = 89
      Top = 17
      Width = 41
      Height = 21
      TabOrder = 1
      Text = '0'
      OnChange = DirectIndexHEditChange
      OnEnter = DirectIndexHEditChange
    end
    object AngleIndexLEdit: TEdit
      Left = 156
      Top = 17
      Width = 41
      Height = 21
      TabOrder = 2
      Text = '0'
      OnChange = DirectIndexHEditChange
      OnEnter = DirectIndexHEditChange
    end
  end
end
