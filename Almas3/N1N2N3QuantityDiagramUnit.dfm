object N1N2N3QuantityDiagramForm: TN1N2N3QuantityDiagramForm
  Left = 0
  Top = 0
  Caption = #1043#1088#1072#1092#1080#1082' '#1080#1079#1084#1077#1085#1077#1085#1080#1103' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1072#1090#1086#1084#1086#1074
  ClientHeight = 351
  ClientWidth = 542
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object N1N2N3Chart: TChart
    Left = 0
    Top = 0
    Width = 542
    Height = 351
    Gradient.EndColor = 13556735
    Gradient.MidColor = 14739177
    Gradient.StartColor = 16774122
    Title.Text.Strings = (
      #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1072#1090#1086#1084#1086#1074' '#1086#1090' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072#1090#1086#1084#1086#1074)
    BottomAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072#1090#1086#1084#1086#1074
    LeftAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1072#1090#1086#1084#1086#1074
    View3D = False
    Align = alClient
    TabOrder = 0
    ExplicitLeft = 208
    ExplicitTop = 72
    object OneLinkSeries: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      SeriesColor = 8421631
      Title = #1054#1076#1085#1086#1089#1074#1103#1079#1085#1099#1077
      LinePen.Color = 8421631
      LinePen.Width = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object TwoLinkSeries: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      Title = #1044#1074#1091#1093#1089#1074#1103#1079#1085#1099#1077
      LinePen.Color = clGreen
      LinePen.Width = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object ThreeLinkSeries: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      SeriesColor = clBlue
      Title = #1058#1088#1077#1093#1089#1074#1103#1079#1085#1099#1077
      LinePen.Color = clBlue
      LinePen.Width = 2
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
end
