object QuantityByGroupeForm: TQuantityByGroupeForm
  Left = 311
  Top = 41
  Caption = #1056#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1072#1090#1086#1084#1086#1074' '#1087#1086' '#1090#1080#1087#1072#1084
  ClientHeight = 539
  ClientWidth = 571
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
  object LayerSplitter: TSplitter
    Left = 177
    Top = 41
    Width = 8
    Height = 498
    ExplicitLeft = 129
    ExplicitHeight = 344
  end
  object QuantityListView: TListView
    Left = 185
    Top = 41
    Width = 386
    Height = 498
    Align = alClient
    Columns = <
      item
        Caption = #1043#1088#1091#1087#1087#1072
        Width = 140
      end
      item
        Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086
        Width = 80
      end>
    GridLines = True
    HideSelection = False
    Items.ItemData = {
      03AC0000000400000000000000FFFFFFFFFFFFFFFF00000000FFFFFFFF000000
      000636003500340036003500340000000000FFFFFFFFFFFFFFFF00000000FFFF
      FFFF00000000142704350442044B04400451044504410432044F0437043D044B
      0435042000300442043E043C044B0400000000FFFFFFFFFFFFFFFF00000000FF
      FFFFFF00000000083600350034003600350034003600350000000000FFFFFFFF
      FFFFFFFF00000000FFFFFFFF0000000000}
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    ExplicitLeft = 132
    ExplicitWidth = 323
    ExplicitHeight = 344
  end
  object LayerTreeView: TTreeView
    Left = 0
    Top = 41
    Width = 177
    Height = 498
    Align = alLeft
    HideSelection = False
    Indent = 19
    ReadOnly = True
    TabOrder = 1
    OnChange = LayerTreeViewChange
    Items.NodeData = {
      03030000002A0000000000000000000000FFFFFFFFFFFFFFFF00000000000000
      000000000001063600350034003600350034002A0000000000000000000000FF
      FFFFFFFFFFFFFF00000000000000000000000001063600350034003600350034
      001E0000000000000000000000FFFFFFFFFFFFFFFF0000000000000000000000
      000100}
    ExplicitHeight = 344
  end
  object ToolPanel: TPanel
    Left = 0
    Top = 0
    Width = 571
    Height = 41
    Align = alTop
    TabOrder = 2
    ExplicitWidth = 455
    object ChartSpeedButton: TSpeedButton
      Left = 2
      Top = 2
      Width = 121
      Height = 37
      Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100' '#1075#1088#1072#1092#1080#1082
      OnClick = ChartSpeedButtonClick
    end
  end
end
