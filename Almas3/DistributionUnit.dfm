object DistributionForm: TDistributionForm
  Left = 0
  Top = 0
  Caption = #1043#1088#1072#1092#1080#1082
  ClientHeight = 542
  ClientWidth = 692
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
  object DistributionChart: TChart
    Left = 0
    Top = 41
    Width = 692
    Height = 501
    Title.Text.Strings = (
      #1043#1080#1089#1090#1086#1088#1075#1088#1072#1084#1084#1072' '#1088#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1103' '#1072#1090#1086#1084#1086#1074' '#1087#1086' '#1074#1077#1088#1086#1103#1090#1085#1086#1089#1090#1103#1084)
    BottomAxis.LabelStyle = talValue
    BottomAxis.MinorTickCount = 0
    BottomAxis.Title.Caption = #1053#1086#1084#1077#1088' '#1074#1077#1088#1086#1103#1090#1085#1086#1089#1090#1080
    LeftAxis.MaximumOffset = 10
    LeftAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1072#1090#1086#1084#1086#1074
    RightAxis.Title.Caption = #1055#1088#1086#1094#1077#1085#1090#1085#1086#1077' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086
    RightAxis.Visible = False
    TopAxis.LabelsAngle = 90
    TopAxis.MinorTickCount = 0
    TopAxis.Title.Caption = #1042#1077#1088#1086#1103#1090#1085#1086#1089#1090#1100
    View3D = False
    Zoom.Animated = True
    Align = alClient
    TabOrder = 0
    PrintMargins = (
      15
      32
      15
      32)
    object DistributionSeries: TBarSeries
      ShowInEditor = False
      HorizAxis = aBothHorizAxis
      Marks.Angle = 90
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Callout.ArrowHeadSize = 0
      Marks.Callout.Length = 10
      Marks.Margins.Units = maPercentSize
      Marks.Shadow.Color = 8487297
      Marks.Style = smsPercent
      Marks.Visible = True
      PercentFormat = '0%'
      SeriesColor = clGray
      VertAxis = aBothVertAxis
      Gradient.Balance = 37
      Gradient.Direction = gdTopBottom
      Gradient.MidColor = 16744576
      Gradient.StartColor = clBlack
      MultiBar = mbNone
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
      Data = {
        04060000000000000000108D40FF0200000041310000000000908A40FF020000
        0041310000000000B88A40FF0200000041310000000000848740FF0100000076
        0000000000B08340FF0200000041310000000000CC8040FF020000004131}
    end
  end
  object ToolPanel: TPanel
    Left = 0
    Top = 0
    Width = 692
    Height = 41
    Align = alTop
    TabOrder = 1
    object AutoScaleSpeedButton: TSpeedButton
      Left = 8
      Top = 11
      Width = 105
      Height = 22
      Caption = #1040#1074#1090#1086#1084#1072#1089#1096#1090#1072#1073
      OnClick = AutoScaleSpeedButtonClick
    end
    object PrecentCheckBox: TCheckBox
      Left = 160
      Top = 18
      Width = 97
      Height = 17
      Caption = #1055#1088#1086#1094#1077#1085#1090#1099
      TabOrder = 0
      OnClick = PrecentCheckBoxClick
    end
    object LegendCheckBox: TCheckBox
      Left = 280
      Top = 18
      Width = 97
      Height = 17
      Caption = #1051#1077#1075#1077#1085#1076#1072
      TabOrder = 1
      OnClick = LegendCheckBoxClick
    end
    object ProbNameCheckBox: TCheckBox
      Left = 360
      Top = 18
      Width = 177
      Height = 17
      Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077'  '#1074#1077#1088#1086#1103#1090#1085#1086#1089#1090#1080
      TabOrder = 2
      OnClick = ProbNameCheckBoxClick
    end
  end
end
