object MainForm: TMainForm
  Left = 8
  Top = 28
  Caption = '3d Grapher'
  ClientHeight = 626
  ClientWidth = 992
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu
  OldCreateOrder = False
  OnActivate = FormActivate
  OnHide = FormHide
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnKeyUp = FormKeyUp
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar: TStatusBar
    Left = 0
    Top = 607
    Width = 992
    Height = 19
    Panels = <>
  end
  object ToolBar: TToolBar
    Left = 0
    Top = 0
    Width = 992
    Height = 48
    ButtonHeight = 47
    Caption = 'ToolBar'
    TabOrder = 1
    object Panel5: TPanel
      Left = 0
      Top = 0
      Width = 75
      Height = 47
      TabOrder = 4
      object CopySpeedButton: TSpeedButton
        Left = 49
        Top = 26
        Width = 23
        Height = 14
        Caption = 'copy '
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        OnClick = CopySpeedButtonClick
      end
      object OpenSpeedButton: TSpeedButton
        Left = 0
        Top = 0
        Width = 33
        Height = 25
        Caption = '1'
        Flat = True
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clPurple
        Font.Height = -19
        Font.Name = 'Wingdings'
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = OpenMenuItemClick
      end
      object ExitSpeedButton: TSpeedButton
        Left = 32
        Top = 0
        Width = 32
        Height = 25
        Caption = #1046
        Flat = True
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clPurple
        Font.Height = -19
        Font.Name = 'Wingdings'
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = ExitMenuItemClick
      end
      object AxisCheckBox: TCheckBox
        Left = 6
        Top = 26
        Width = 40
        Height = 17
        Caption = #1054#1089#1080
        Checked = True
        State = cbChecked
        TabOrder = 0
        OnClick = AxisCheckBoxClick
      end
    end
    object Panel2: TPanel
      Left = 75
      Top = 0
      Width = 104
      Height = 47
      TabOrder = 0
      object MillersIndexesLabel: TLabel
        Left = 2
        Top = 11
        Width = 81
        Height = 12
        Caption = 'MillersIndexesLabel'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object MillersLabel: TLabel
        Left = 2
        Top = 1
        Width = 80
        Height = 12
        Caption = #1048#1085#1076#1077#1082#1089#1099' '#1052#1080#1083#1083#1077#1088#1072':'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object OrthoLabel: TLabel
        Left = 2
        Top = 21
        Width = 86
        Height = 12
        Caption = #1055#1077#1088#1087#1077#1085#1076#1080#1082#1091#1083#1103#1088#1085#1099#1077':'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object OrthoMillersIndexesLabel: TLabel
        Left = 2
        Top = 32
        Width = 104
        Height = 12
        Caption = 'OrthoMillersIndexesLabel'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
    end
    object Panel3: TPanel
      Left = 179
      Top = 0
      Width = 96
      Height = 47
      TabOrder = 1
      object StepUpSpeedButton: TSpeedButton
        Left = 3
        Top = 3
        Width = 10
        Height = 10
        Hint = #1059#1074#1077#1083#1080#1095#1080#1090#1100' (F9) '#1087#1077#1088#1077#1084#1077#1097#1077#1085#1080#1103' '#1074' 2 '#1088#1072#1079#1072
        AllowAllUp = True
        Glyph.Data = {
          86000000424D8600000000000000760000002800000005000000040000000100
          0400000000001000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFF0000000
          0000F000F000FF0FF000}
        Layout = blGlyphRight
        ParentShowHint = False
        ShowHint = True
        OnClick = StepUpSpeedButtonClick
      end
      object StepDownSpeedButton: TSpeedButton
        Left = 3
        Top = 12
        Width = 10
        Height = 10
        Hint = #1059#1084#1077#1085#1100#1096#1080#1090#1100' (F10) '#1087#1077#1088#1077#1084#1077#1097#1077#1085#1080#1103' '#1074' 2 '#1088#1072#1079#1072
        AllowAllUp = True
        BiDiMode = bdLeftToRight
        Glyph.Data = {
          86000000424D8600000000000000760000002800000005000000040000000100
          0400000000001000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FF0FF000F000
          F00000000000FFFFF000}
        Layout = blGlyphRight
        ParentShowHint = False
        ParentBiDiMode = False
        ShowHint = True
        OnClick = StepDownSpeedButtonClick
      end
      object MulSpeedLabel: TLabel
        Left = 14
        Top = 6
        Width = 74
        Height = 13
        Caption = 'MulSpeedLabel'
      end
      object SpeedButton1: TSpeedButton
        Left = 3
        Top = 24
        Width = 10
        Height = 10
        Hint = #1059#1074#1077#1083#1080#1095#1080#1090#1100' (F11) '#1091#1075#1086#1083#1099' '#1074' 2 '#1088#1072#1079#1072
        AllowAllUp = True
        BiDiMode = bdLeftToRight
        Glyph.Data = {
          86000000424D8600000000000000760000002800000005000000040000000100
          0400000000001000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFF0000000
          0000F000F000FF0FF000}
        Layout = blGlyphRight
        ParentShowHint = False
        ParentBiDiMode = False
        ShowHint = True
        OnClick = AngleUpSpeedButtonClick
      end
      object SpeedButton2: TSpeedButton
        Left = 3
        Top = 33
        Width = 10
        Height = 10
        Hint = #1059#1084#1077#1085#1100#1096#1080#1090#1100' (F12) '#1091#1075#1086#1083#1099' '#1074' 2 '#1088#1072#1079#1072
        AllowAllUp = True
        BiDiMode = bdLeftToRight
        Glyph.Data = {
          86000000424D8600000000000000760000002800000005000000040000000100
          0400000000001000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FF0FF000F000
          F00000000000FFFFF000}
        Layout = blGlyphRight
        ParentShowHint = False
        ParentBiDiMode = False
        ShowHint = True
        OnClick = AngleDownSpeedButtonClick
      end
      object MulAngleLabel: TLabel
        Left = 14
        Top = 27
        Width = 70
        Height = 13
        Caption = 'MulAngleLabel'
      end
    end
    object Panel4: TPanel
      Left = 275
      Top = 0
      Width = 104
      Height = 47
      TabOrder = 2
      object RightMoveSpeedButton: TSpeedButton
        Left = 5
        Top = 3
        Width = 14
        Height = 14
        Hint = 
          #1057#1084#1077#1097#1077#1085#1080#1077' '#1074#1076#1086#1083#1100' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1075#1086' '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1103' '#1087#1086' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' X ('#1082#1083 +
          #1072#1074#1080#1096#1072' <)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFF00
          0000FFFFFFFFFF000000FF9FFFFFFF000000F99FFFFFFF000000999999999900
          00009999999999000000F99FFFFFFF000000FF9FFFFFFF000000FFFFFFFFFF00
          0000FFFFFFFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = RightMoveSpeedButtonClick
      end
      object LeftMoveSpeedButtonSpeedButton: TSpeedButton
        Left = 18
        Top = 3
        Width = 14
        Height = 14
        Hint = 
          #1057#1084#1077#1097#1077#1085#1080#1077' '#1074#1076#1086#1083#1100' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1075#1086' '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1103' '#1087#1086' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' X ('#1082#1083 +
          #1072#1074#1080#1096#1072' L)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFF00
          0000FFFFFFFFFF000000FFFFFFF9FF000000FFFFFFF99F000000999999999900
          00009999999999000000FFFFFFF99F000000FFFFFFF9FF000000FFFFFFFFFF00
          0000FFFFFFFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = LeftMoveSpeedButtonSpeedButtonClick
      end
      object UpMoveSpeedButton: TSpeedButton
        Left = 37
        Top = 3
        Width = 14
        Height = 14
        Hint = 
          #1057#1084#1077#1097#1077#1085#1080#1077' '#1074#1076#1086#1083#1100' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1075#1086' '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1103' '#1087#1086' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Y ('#1082#1083 +
          #1072#1074#1080#1096#1072' :)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFAAFFFF00
          0000FFFFAAFFFF000000FFFFAAFFFF000000FFFFAAFFFF000000FFFFAAFFFF00
          0000FFFFAAFFFF000000FFFFAAFFFF000000FFAAAAAAFF000000FFFAAAAFFF00
          0000FFFFAAFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = UpMoveSpeedButtonClick
      end
      object DownMoveSpeedButton: TSpeedButton
        Left = 50
        Top = 3
        Width = 14
        Height = 14
        Hint = 
          #1057#1084#1077#1097#1077#1085#1080#1077' '#1074#1076#1086#1083#1100' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1075#1086' '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1103' '#1087#1086' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Y ('#1082#1083 +
          #1072#1074#1080#1096#1072' >)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFAAFFFF00
          0000FFFAAAAFFF000000FFAAAAAAFF000000FFFFAAFFFF000000FFFFAAFFFF00
          0000FFFFAAFFFF000000FFFFAAFFFF000000FFFFAAFFFF000000FFFFAAFFFF00
          0000FFFFAAFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = DownMoveSpeedButtonClick
      end
      object FrontMoveSpeedButton: TSpeedButton
        Left = 70
        Top = 3
        Width = 14
        Height = 14
        Hint = 
          #1057#1084#1077#1097#1077#1085#1080#1077' '#1074#1076#1086#1083#1100' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1075#1086' '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1103' '#1087#1086' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Z ('#1082#1083 +
          #1072#1074#1080#1096#1072' ")'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFF00
          0000FCCCCCFFFF000000FCCCCFFFFF000000FCCCCFFFFF000000FCCCCCFFFF00
          0000FCFFCCCFFF000000FFFFFCCCFF000000FFFFFFCCCF000000FFFFFFFCCC00
          0000FFFFFFFFCF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = FrontMoveSpeedButtonClick
      end
      object BackMoveSpeedButton: TSpeedButton
        Left = 83
        Top = 3
        Width = 14
        Height = 14
        Hint = 
          #1057#1084#1077#1097#1077#1085#1080#1077' '#1074#1076#1086#1083#1100' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1075#1086' '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1103' '#1087#1086' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Z ('#1082#1083 +
          #1072#1074#1080#1096#1072' ?)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFF00
          0000FCCFFFFFFF000000FCCCFFFFFF000000FFCCCFFFFF000000FFFCCCFFFF00
          0000FFFFCCCFFC000000FFFFFCCCCC000000FFFFFFCCCC000000FFFFFFCCCC00
          0000FFFFFCCCCC000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = BackMoveSpeedButtonClick
      end
      object XLocalBackSpeedButton: TSpeedButton
        Left = 5
        Top = 16
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' X '#1074' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083#1072 +
          #1074#1080#1096#1072' S)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF999FFFF00
          0000FF99FFFFFF000000F99FFFFFFF000000F9FFFFFFFF000000999999999900
          0000F9FFFFFFFF000000F99FF9FFFF000000FF999999FF000000FFFF999FFF00
          0000FFFFF9FFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = XLocalBackSpeedButtonClick
      end
      object XLocalFrontSpeedButton: TSpeedButton
        Left = 18
        Top = 16
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' X '#1074' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083#1072 +
          #1074#1080#1096#1072' W)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFF999FFF00
          0000FFFFFF99FF000000FFFFFFF99F000000FFFFFFFF9F000000999999999900
          0000FFFFFFFF9F000000FFFF9FF99F000000FF999999FF000000FFF999FFFF00
          0000FFFF9FFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = XLocalFrontSpeedButtonClick
      end
      object YLocalRightSpeedButton: TSpeedButton
        Left = 37
        Top = 16
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Y '#1074' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083#1072 +
          #1074#1080#1096#1072' A)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFAFFFF00
          0000FFFAAAAAFF000000FFAAFAFAAF000000FFAFFAFFAA000000FAAFFAFFFA00
          0000AAAAFAFFFA000000FAAFFAFFFF000000FFAFFAFFFF000000FFFFFAFFFF00
          0000FFFFFAFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = YLocalRightSpeedButtonClick
      end
      object YLocalLeftSpeedButton: TSpeedButton
        Left = 50
        Top = 16
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Y '#1074' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083#1072 +
          #1074#1080#1096#1072' D)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFAFFFFF00
          0000FFAAAAAFFF000000FAAFAFAAFF000000AAFFAFFAFF000000AFFFAFFAAF00
          0000AFFFAFAAAA000000FFFFAFFAAF000000FFFFAFFAFF000000FFFFAFFFFF00
          0000FFFFAFFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = YLocalLeftSpeedButtonClick
      end
      object ZLocalClockwiseSpeedButton: TSpeedButton
        Left = 70
        Top = 16
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Z '#1074' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083#1072 +
          #1074#1080#1096#1072' E)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFCCCFFF00
          0000FCFCFFFCFF000000FFCFFFFFFF000000FCFCFFFFFF000000CFFFCFFFFF00
          0000CFFFFCFFFF000000CFFCFFCFFF000000FCCCFFFCFF000000FCCCFFFFCF00
          0000CCCCFFFFFC000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = ZLocalClockwiseSpeedButtonClick
      end
      object ZLocalAnticlockwiseSpeedButton: TSpeedButton
        Left = 83
        Top = 16
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1083#1086#1082#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Z '#1074' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083#1072 +
          #1074#1080#1096#1072' Q)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFCCCFFC00
          0000FCFCFFFCCC000000FFCFFFFCCC000000FCFCFFCCCC000000CFFFCFFFFF00
          0000CFFFFCFFFF000000CFFFFFCFFF000000FCFFFFFCFF000000FFFFFFFFCF00
          0000FFFFFFFFFC000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = ZLocalAnticlockwiseSpeedButtonClick
      end
      object XGlobalBackSpeedButton: TSpeedButton
        Left = 5
        Top = 29
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1075#1083#1086#1073#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' X '#1074' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083 +
          #1072#1074#1080#1096#1072' V)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF999FFFF00
          0000FF99FFFFFF000000F99FFFFFFF000000F9FFFFFFFF000000999999999900
          0000F9FFFFFFFF000000F99FF9FFFF000000FF999999FF000000FFFF999FFF00
          0000FFFFF9FFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = XGlobalBackSpeedButtonClick
      end
      object XGlobalFrontSpeedButton: TSpeedButton
        Left = 18
        Top = 29
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1075#1083#1086#1073#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' X '#1074' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083 +
          #1072#1074#1080#1096#1072' G)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFF999FFF00
          0000FFFFFF99FF000000FFFFFFF99F000000FFFFFFFF9F000000999999999900
          0000FFFFFFFF9F000000FFFF9FF99F000000FF999999FF000000FFF999FFFF00
          0000FFFF9FFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = XGlobalFrontSpeedButtonClick
      end
      object YGlobalRightSpeedButton: TSpeedButton
        Left = 37
        Top = 29
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1075#1083#1086#1073#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Y '#1074' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083 +
          #1072#1074#1080#1096#1072' C)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFAFFFF00
          0000FFFAAAAAFF000000FFAAFAFAAF000000FFAFFAFFAA000000FAAFFAFFFA00
          0000AAAAFAFFFA000000FAAFFAFFFF000000FFAFFAFFFF000000FFFFFAFFFF00
          0000FFFFFAFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = YGlobalRightSpeedButtonClick
      end
      object YGlobalLeftSpeedButton: TSpeedButton
        Left = 50
        Top = 29
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1075#1083#1086#1073#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Y '#1074' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083 +
          #1072#1074#1080#1096#1072' B)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFAFFFFF00
          0000FFAAAAAFFF000000FAAFAFAAFF000000AAFFAFFAFF000000AFFFAFFAAF00
          0000AFFFAFAAAA000000FFFFAFFAAF000000FFFFAFFAFF000000FFFFAFFFFF00
          0000FFFFAFFFFF000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = YGlobalLeftSpeedButtonClick
      end
      object ZGlobalClockwiseSpeedButton: TSpeedButton
        Left = 70
        Top = 29
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1075#1083#1086#1073#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Z '#1074' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083 +
          #1072#1074#1080#1096#1072' F)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFCCCFFF00
          0000FCFCFFFCFF000000FFCFFFFFFF000000FCFCFFFFFF000000CFFFCFFFFF00
          0000CFFFFCFFFF000000CFFCFFCFFF000000FCCCFFFCFF000000FCCCFFFFCF00
          0000CCCCFFFFFC000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = ZGlobalClockwiseSpeedButtonClick
      end
      object ZGlobalAnticlockwiseSpeedButton: TSpeedButton
        Left = 83
        Top = 29
        Width = 14
        Height = 14
        Hint = 
          #1055#1086#1074#1086#1088#1086#1090' '#1074#1086#1082#1088#1091#1075' '#1075#1083#1086#1073#1072#1083#1100#1085#1086#1081' '#1086#1089#1080' Z '#1074' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1086#1084'  '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1080#1080' ('#1082#1083 +
          #1072#1074#1080#1096#1072' H)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFCCCFFC00
          0000FCFCFFFCCC000000FFCFFFFCCC000000FCFCFFCCCC000000CFFFCFFFFF00
          0000CFFFFCFFFF000000CFFFFFCFFF000000FCFFFFFCFF000000FFFFFFFFCF00
          0000FFFFFFFFFC000000}
        ParentShowHint = False
        ShowHint = True
        OnClick = ZGlobalAnticlockwiseSpeedButtonClick
      end
    end
    object Panel1: TPanel
      Left = 379
      Top = 0
      Width = 270
      Height = 47
      TabOrder = 3
      object INSpeedButton: TSpeedButton
        Left = 1
        Top = 2
        Width = 15
        Height = 15
        Hint = #1059#1074#1077#1083#1080#1095#1077#1085#1080#1077' ('#1082#1083#1072#1074#1080#1096#1072' i)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF0000FFF00
          0000FF0DDDD0FF000000F0DD00DD0F0000000DDD00DDD00000000D000000D000
          00000D000000D00000000DDD00DDD0000000F0DD00DD0F000000FF0DDDD0FF00
          0000FFF0000FFF000000}
        Layout = blGlyphRight
        ParentShowHint = False
        ShowHint = True
        OnClick = INSpeedButtonClick
      end
      object ScaleLabel: TLabel
        Left = 30
        Top = 3
        Width = 46
        Height = 13
        Caption = #1052#1072#1089#1096#1090#1072#1073
      end
      object OUTSpeedButton: TSpeedButton
        Left = 14
        Top = 2
        Width = 15
        Height = 15
        Hint = #1059#1084#1077#1085#1100#1096#1077#1085#1080#1077' ('#1082#1083#1072#1074#1080#1096#1072' o)'
        AllowAllUp = True
        Glyph.Data = {
          C6000000424DC60000000000000076000000280000000A0000000A0000000100
          0400000000005000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF0000FFF00
          0000FF0DDDD0FF000000F0DDDDDD0F0000000DDDDDDDD00000000D000000D000
          00000D000000D00000000DDDDDDDD0000000F0DDDDDD0F000000FF0DDDD0FF00
          0000FFF0000FFF000000}
        Layout = blGlyphRight
        ParentShowHint = False
        ShowHint = True
        OnClick = OUTSpeedButtonClick
      end
      object InfoSpeedButton: TSpeedButton
        Left = 85
        Top = 19
        Width = 23
        Height = 22
        AllowAllUp = True
        GroupIndex = -1
        Caption = 'i'
        Flat = True
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = InfoSpeedButtonClick
      end
      object SaveOrientationSpeedButton: TSpeedButton
        Left = 114
        Top = 24
        Width = 24
        Height = 17
        Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1102'|'
        AllowAllUp = True
        Caption = '>>'
        ParentShowHint = False
        ShowHint = True
        OnClick = SaveOrientationSpeedButtonClick
      end
      object MillersSpeedButton: TSpeedButton
        Left = 114
        Top = 3
        Width = 27
        Height = 17
        Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1102'|'
        AllowAllUp = True
        Caption = '(-;-;-)'
        ParentShowHint = False
        ShowHint = True
        OnClick = MillersSpeedButtonClick
      end
      object SaveOrientationListSpeedButton: TSpeedButton
        Left = 147
        Top = 3
        Width = 38
        Height = 15
        Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1089#1087#1080#1089#1086#1082' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1081
        Caption = #1057#1086#1093#1088'.'
        Flat = True
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        OnClick = SaveOrientationListSpeedButtonClick
      end
      object OpenOrientationListSpeedButton: TSpeedButton
        Left = 191
        Top = 3
        Width = 38
        Height = 15
        Hint = #1054#1090#1082#1088#1099#1090#1100' '#1089#1087#1080#1089#1086#1082' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1081
        Caption = #1054#1090#1082#1088'.'
        Flat = True
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        OnClick = OpenOrientationListSpeedButtonClick
      end
      object MillersComboBox: TComboBox
        Left = 5
        Top = 20
        Width = 78
        Height = 21
        Hint = #1042#1099#1073#1088#1072#1090#1100' '#1089#1090#1072#1076#1072#1088#1090#1085#1091#1102' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1102' '#1080#1079' '#1089#1087#1080#1089#1082#1072'|'
        Style = csDropDownList
        DropDownCount = 100
        ImeName = '1'
        ItemHeight = 13
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        TabStop = False
        OnChange = MillersComboBoxChange
        OnClick = MillersComboBoxDropDown
        OnDropDown = MillersComboBoxDropDown
        Items.Strings = (
          '(0:0:1)*'
          '(0:-1:0)'
          '(1:0:0)'
          '(1:-1:0)*'
          '(0:0:-1)'
          '(1:1:0)'
          '(1:0:1) '
          '(0:1:1) '
          '(-1:-1:1)*'
          '(0:1:1) '
          '(1:0:1) '
          '(1:1:2) ')
      end
      object SaveOrientationComboBox: TComboBox
        Left = 133
        Top = 20
        Width = 130
        Height = 21
        Hint = #1042#1099#1073#1088#1072#1090#1100' '#1089#1086#1093#1088#1072#1085#1105#1085#1085#1091#1102' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1102' '#1080#1079' '#1089#1087#1080#1089#1082#1072
        Style = csDropDownList
        ImeName = '1'
        ItemHeight = 13
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        TabStop = False
        OnChange = SaveOrientationComboBoxChange
        OnCloseUp = SaveOrientationComboBoxCloseUp
        OnDropDown = MillersComboBoxDropDown
        Items.Strings = (
          #1054#1090#1084#1077#1085#1072)
      end
    end
    object Panel6: TPanel
      Left = 649
      Top = 0
      Width = 210
      Height = 47
      TabOrder = 5
      object CxLabel: TLabel
        Left = 5
        Top = 30
        Width = 9
        Height = 13
        Caption = 'X'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object CyLabel: TLabel
        Left = 72
        Top = 30
        Width = 9
        Height = 13
        Caption = 'Y'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object CzLabel: TLabel
        Left = 141
        Top = 30
        Width = 9
        Height = 13
        Caption = 'Z'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object CenterSpeedButton: TSpeedButton
        Left = 140
        Top = 16
        Width = 67
        Height = 14
        Caption = #1062#1077#1085#1090#1088#1080#1088#1086#1074#1072#1090#1100
        Flat = True
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        OnClick = CenterSpeedButtonClick
      end
      object AutocenterSpeedButton: TSpeedButton
        Left = 112
        Top = 2
        Width = 95
        Height = 15
        Caption = #1040#1074#1090#1086#1094#1077#1085#1090#1088#1088#1080#1088#1086#1074#1072#1085#1080#1077
        Flat = True
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        OnClick = AutocenterSpeedButtonClick
      end
      object CxEdit: TEdit
        Left = 16
        Top = 30
        Width = 54
        Height = 14
        AutoSize = False
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnEnter = CxEditEnter
        OnExit = CxEditExit
        OnKeyDown = CxEditKeyDown
      end
      object CyEdit: TEdit
        Left = 83
        Top = 30
        Width = 54
        Height = 14
        AutoSize = False
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnEnter = CxEditEnter
        OnExit = CxEditExit
        OnKeyDown = CxEditKeyDown
      end
      object CzEdit: TEdit
        Left = 151
        Top = 31
        Width = 54
        Height = 14
        AutoSize = False
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnEnter = CxEditEnter
        OnExit = CxEditExit
        OnKeyDown = CxEditKeyDown
      end
      object ObjectCenterComboBox: TComboBox
        Left = 8
        Top = 2
        Width = 105
        Height = 22
        Hint = #1042#1099#1073#1088#1072#1090#1100' '#1089#1090#1072#1076#1072#1088#1090#1085#1091#1102' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1102' '#1080#1079' '#1089#1087#1080#1089#1082#1072'|'
        Style = csDropDownList
        DropDownCount = 20
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ImeName = '1'
        ItemHeight = 14
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        TabStop = False
        OnChange = ObjectCenterComboBoxChange
        Items.Strings = (
          '(0:0:1)*'
          '(0:-1:0)'
          '(1:0:0)'
          '(1:-1:0)*'
          '(0:0:-1)'
          '(1:1:0)'
          '(1:0:1) '
          '(0:1:1) '
          '(-1:-1:1)*'
          '(0:1:1) '
          '(1:0:1) '
          '(1:1:2) ')
      end
    end
    object Panel7: TPanel
      Left = 859
      Top = 0
      Width = 132
      Height = 47
      TabOrder = 6
      object DiamUpSpeedButton: TSpeedButton
        Left = 3
        Top = 24
        Width = 10
        Height = 10
        Hint = #1059#1074#1077#1083#1080#1095#1080#1090#1100' (F11) '#1091#1075#1086#1083#1099' '#1074' 2 '#1088#1072#1079#1072
        AllowAllUp = True
        BiDiMode = bdLeftToRight
        Glyph.Data = {
          86000000424D8600000000000000760000002800000005000000040000000100
          0400000000001000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFF0000000
          0000F000F000FF0FF000}
        Layout = blGlyphRight
        ParentShowHint = False
        ParentBiDiMode = False
        ShowHint = True
        OnClick = DiamUpSpeedButtonClick
      end
      object DiamDownSpeedButton: TSpeedButton
        Left = 3
        Top = 33
        Width = 10
        Height = 10
        Hint = #1059#1084#1077#1085#1100#1096#1080#1090#1100' (F12) '#1091#1075#1086#1083#1099' '#1074' 2 '#1088#1072#1079#1072
        AllowAllUp = True
        BiDiMode = bdLeftToRight
        Glyph.Data = {
          86000000424D8600000000000000760000002800000005000000040000000100
          0400000000001000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FF0FF000F000
          F00000000000FFFFF000}
        Layout = blGlyphRight
        ParentShowHint = False
        ParentBiDiMode = False
        ShowHint = True
        OnClick = DiamDownSpeedButtonClick
      end
      object DiamLabel: TLabel
        Left = 14
        Top = 27
        Width = 50
        Height = 13
        Caption = 'DiamLabel'
      end
      object DrawLineCheckBox: TCheckBox
        Left = 77
        Top = 5
        Width = 54
        Height = 15
        Caption = #1051#1080#1085#1080#1080
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object DrawSpherasCheckBox: TCheckBox
        Left = 77
        Top = 26
        Width = 50
        Height = 15
        Caption = #1064#1072#1088#1099
        Checked = True
        State = cbChecked
        TabOrder = 1
      end
      object DrawCilindersCheckBox: TCheckBox
        Left = 3
        Top = 5
        Width = 73
        Height = 15
        Caption = #1062#1080#1083#1080#1085#1076#1088#1099
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
    end
  end
  object OpenGLPanel: TPanel
    Left = 0
    Top = 48
    Width = 992
    Height = 559
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    OnMouseMove = OpenGLPanelMouseMove
    OnResize = OpenGLPanelResize
  end
  object MainMenu: TMainMenu
    Left = 536
    Top = 72
    object FileMenuItem: TMenuItem
      Caption = #1060#1072#1081#1083
      object OpenMenuItem: TMenuItem
        Caption = '&'#1054#1090#1082#1088#1099#1090#1100
        OnClick = OpenMenuItemClick
      end
      object ExitMenuItem: TMenuItem
        Caption = '&'#1042#1099#1093#1086#1076
        OnClick = ExitMenuItemClick
      end
    end
    object N1: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      object WhiteBackgroundMenuItem: TMenuItem
        Caption = #1041#1077#1083#1099#1081' '#1092#1086#1085
        OnClick = WhiteBackgroundMenuItemClick
      end
    end
  end
  object ApplicationEvents: TApplicationEvents
    OnIdle = ApplicationEventsIdle
    Left = 568
    Top = 69
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'txt'
    Filter = #1058#1077#1082#1089#1090#1086#1074#1099#1077' '#1092#1072#1081#1083#1099' (*.txt)|*.txt|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Left = 504
    Top = 74
  end
  object OrientationSaveDialog: TSaveDialog
    DefaultExt = 'orn'
    Filter = #1057#1087#1080#1086#1082' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1081' (*.orn)|*.orn|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = #1057#1086#1093#1088#1072#1085#1080#1077#1085#1080#1077' '#1089#1087#1080#1089#1082#1072' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1081
    Left = 552
    Top = 136
  end
  object OrientationOpenDialog: TOpenDialog
    DefaultExt = 'orn'
    Filter = #1057#1087#1080#1086#1082' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1081' (*.orn)|*.orn|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Title = #1054#1090#1082#1088#1099#1090#1080#1077' '#1089#1087#1080#1089#1082#1072' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1081
    Left = 520
    Top = 136
  end
end
