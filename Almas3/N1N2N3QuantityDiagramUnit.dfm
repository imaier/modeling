object N1N2N3QuantityDiagramForm: TN1N2N3QuantityDiagramForm
  Left = 0
  Top = 0
  Caption = #1057#1072#1090#1080#1089#1090#1080#1082#1072' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1072#1090#1086#1084#1086#1074
  ClientHeight = 541
  ClientWidth = 903
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object StatisticPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 903
    Height = 541
    ActivePage = AtomQuantityByDeleteAtomQuantityTabSheet
    Align = alClient
    TabOrder = 0
    object AtomQuantityByDeleteAtomQuantityTabSheet: TTabSheet
      Caption = 
        #1043#1088#1072#1092#1080#1082' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1072#1090#1086#1084#1086#1074' '#1086#1090' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072 +
        #1090#1086#1084#1086#1074
      ExplicitLeft = 0
      ExplicitWidth = 466
      ExplicitHeight = 389
      object N1N2N3Chart: TChart
        Left = 0
        Top = 0
        Width = 895
        Height = 513
        Gradient.EndColor = 13556735
        Gradient.MidColor = 14739177
        Gradient.StartColor = 16774122
        MarginBottom = 3
        MarginLeft = 1
        MarginRight = 4
        MarginTop = 3
        Title.Text.Strings = (
          
            #1043#1088#1072#1092#1080#1082' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1072#1090#1086#1084#1086#1074' '#1086#1090' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072 +
            #1090#1086#1084#1086#1074)
        BottomAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072#1090#1086#1084#1086#1074
        LeftAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1072#1090#1086#1084#1086#1074
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        ExplicitLeft = 41
        ExplicitTop = 38
        ExplicitWidth = 425
        ExplicitHeight = 351
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
        object PopularTypeSeries: TFastLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          SeriesColor = 33023
          Title = #1055#1086#1087#1091#1083#1103#1088#1085#1099#1081' '#1090#1080#1087
          LinePen.Color = 33023
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object nS_Series: TFastLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          SeriesColor = clMaroon
          Title = #1042#1090#1086#1088#1099#1077' '#1085#1077#1087#1088#1103#1084#1099#1077' '
          LinePen.Color = clMaroon
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
    object QuantityDeletedAtomByAtomTypeTabSheet: TTabSheet
      Caption = #1043#1088#1072#1092#1080#1082' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072#1090#1086#1084#1086#1074' '#1086#1090' '#1090#1080#1087#1072' '#1072#1090#1086#1084#1072
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitWidth = 466
      ExplicitHeight = 389
      object QuantityDeletedAtomByAtomTypeChart: TChart
        Left = 0
        Top = 0
        Width = 895
        Height = 513
        Legend.Visible = False
        MarginBottom = 3
        MarginLeft = 1
        MarginRight = 4
        MarginTop = 3
        Title.Text.Strings = (
          #1043#1088#1072#1092#1080#1082' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072#1090#1086#1084#1086#1074' '#1086#1090' '#1090#1080#1087#1072' '#1072#1090#1086#1084#1072)
        Title.VertMargin = 0
        BottomAxis.ExactDateTime = False
        BottomAxis.Increment = 1.000000000000000000
        BottomAxis.LabelsAngle = 270
        BottomAxis.LabelsSeparation = 0
        BottomAxis.MinorTickCount = 0
        BottomAxis.TickOnLabelsOnly = False
        BottomAxis.Title.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1074#1077#1088#1086#1103#1090#1085#1086#1089#1090#1080
        LeftAxis.MaximumOffset = 15
        LeftAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072#1090#1086#1084#1086#1074
        TopAxis.LabelStyle = talValue
        TopAxis.MinorTickCount = 0
        TopAxis.Title.Caption = #1058#1080#1087' '#1072#1090#1086#1084#1072
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        ExplicitLeft = 48
        ExplicitTop = 32
        ExplicitWidth = 400
        ExplicitHeight = 250
        PrintMargins = (
          15
          21
          15
          21)
        object QuantityDeletedAtomByAtomTypeSeries: TBarSeries
          HorizAxis = aBothHorizAxis
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Shadow.Color = 8487297
          Marks.Style = smsValue
          Marks.Visible = False
          Title = 'DeletedAtomByAtomTypeSeries'
          Gradient.Direction = gdTopBottom
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
      end
    end
  end
end
