object DefectEditForm: TDefectEditForm
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1044#1077#1092#1077#1082#1090
  ClientHeight = 158
  ClientWidth = 290
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object CountLabel: TLabel
    Left = 10
    Top = 74
    Width = 99
    Height = 13
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1094#1080#1082#1083#1086#1074
  end
  object NameLabel: TLabel
    Left = 10
    Top = 49
    Width = 48
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077
  end
  object PictSpeedButton: TSpeedButton
    Left = 262
    Top = 98
    Width = 20
    Height = 20
    Enabled = False
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000120B0000120B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
      5555555555FFFFF5555555555000005555555555F777775FF555555008877700
      55555557755FFF775F55550887000777055555755F777FFF75F550880FBFBF07
      705557F57755577FF7F55080F00000F07055575755777557F75F087F00B3300F
      77057F5757555757FF7F080B0B3B330B07057F757F5555757F7F0F0F0BBBB30F
      07057F757F5555757F7F0F0B0FBB3B0B08057F757FF55575757F0F7F00FFB00F
      780575F757FFF757F5755080F00000F0805557F75577755757F550F80FBFBF08
      8055575F775557755755550F8700078805555575FF77755F755555500FFF8800
      5555555775FFFF77555555555000005555555555577777555555}
    NumGlyphs = 2
    OnClick = PictSpeedButtonClick
  end
  object MaskLabel: TLabel
    Left = 10
    Top = 100
    Width = 31
    Height = 13
    Caption = #1052#1072#1089#1082#1072
  end
  object HelpLabel: TLabel
    Left = 8
    Top = 1
    Width = 247
    Height = 39
    Caption = 
      #1044#1077#1092#1077#1082#1090' '#1087#1088#1080#1084#1077#1085#1103#1077#1090#1089#1103'  '#1087#1086#1089#1090#1088#1077#1076#1089#1074#1086#1084' '#1085#1072#1085#1077#1089#1077#1085#1080#1103' '#1080' '#1091#1076#1072#1083#1077#1085#1080#1103'  '#1086#1087#1088#1077#1076#1077#1083#1077#1085#1085 +
      #1086#1081' '#1084#1072#1089#1082#1080' '#1085#1077#1082#1086#1090#1086#1088#1086#1077' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1088#1072#1079'.'
    WordWrap = True
  end
  object ButtonsPanel: TPanel
    Left = 0
    Top = 127
    Width = 290
    Height = 31
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitTop = 228
    ExplicitWidth = 288
    object OkPanel: TPanel
      Left = 157
      Top = 0
      Width = 68
      Height = 31
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 155
      object Label1: TLabel
        Left = -160
        Top = -248
        Width = 31
        Height = 13
        Caption = 'Label1'
      end
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
      Left = 225
      Top = 0
      Width = 65
      Height = 31
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 1
      ExplicitLeft = 223
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
  object CountEdit: TEdit
    Left = 161
    Top = 71
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'CountEdit'
  end
  object NameEdit: TEdit
    Left = 64
    Top = 46
    Width = 218
    Height = 21
    TabOrder = 2
    Text = 'NameEdit'
  end
  object EditBitBtn: TBitBtn
    Left = 161
    Top = 98
    Width = 95
    Height = 20
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1084#1072#1089#1082#1091
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 3
    OnClick = EditBitBtnClick
  end
  object MaskSaveDialog: TSaveDialog
    DefaultExt = 'msk'
    Filter = #1060#1072#1081#1083#1099' '#1086#1087#1080#1089#1072#1085#1080#1103' '#1084#1072#1089#1082#1080' (*.msk)|*.msk|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = #1057#1086#1093#1088#1072#1085#1077#1085#1080#1077' '#1084#1072#1089#1082#1080' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1080
    Left = 209
    Top = 500
  end
  object MaskOpenDialog: TOpenDialog
    DefaultExt = 'msk'
    Filter = #1060#1072#1081#1083#1099' '#1086#1087#1080#1089#1072#1085#1080#1103' '#1084#1072#1089#1082#1080' (*.msk)|*.msk|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Title = #1054#1090#1082#1088#1099#1090#1080#1077' '#1084#1072#1089#1082#1080' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1080
    Left = 128
    Top = 500
  end
end
