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
    ActivePage = RoughnessTabSheet
    Align = alClient
    TabOrder = 0
    object AtomQuantityByDeleteAtomQuantityTabSheet: TTabSheet
      Caption = 
        #1043#1088#1072#1092#1080#1082' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1085#1099#1093' '#1072#1090#1086#1084#1086#1074' '#1086#1090' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072 +
        #1090#1086#1084#1086#1074
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
        object SaveImageSpeedButton: TSpeedButton
          Left = 0
          Top = 0
          Width = 137
          Height = 22
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077
          OnClick = SaveImageSpeedButtonClick
        end
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
    object ParametricGraphTabSheet: TTabSheet
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1080#1095#1077#1089#1082#1080#1081' '#1075#1088#1072#1092#1080#1082
      ImageIndex = 2
      object ParametriсChart: TChart
        Left = 0
        Top = 0
        Width = 895
        Height = 513
        Gradient.EndColor = 13556735
        Gradient.MidColor = 14739177
        Gradient.StartColor = 16774122
        Legend.Visible = False
        MarginBottom = 3
        MarginLeft = 1
        MarginRight = 4
        MarginTop = 3
        Title.Text.Strings = (
          
            #1055#1072#1088#1072#1084#1077#1090#1088#1080#1095#1077#1089#1082#1080#1081' '#1075#1088#1072#1092#1080#1082' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1086#1076#1085#1086#1075#1086' '#1090#1080#1087#1072' '#1072#1090#1086#1084#1086#1074' '#1086#1090' '#1076#1088#1091#1075#1086#1075#1086' ' +
            #1090#1080#1087#1072' '#1072#1090#1086#1084#1086#1074)
        BottomAxis.LabelsOnAxis = False
        BottomAxis.LabelStyle = talValue
        BottomAxis.MinorTickCount = 0
        BottomAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1076#1088#1091#1075#1086#1075#1086' '#1090#1080#1088#1087#1072' '#1072#1090#1086#1084#1086#1074
        DepthAxis.Automatic = False
        DepthAxis.AutomaticMaximum = False
        DepthAxis.AutomaticMinimum = False
        DepthAxis.Maximum = 0.650000000000000100
        DepthAxis.Minimum = -0.350000000000000000
        DepthTopAxis.Automatic = False
        DepthTopAxis.AutomaticMaximum = False
        DepthTopAxis.AutomaticMinimum = False
        DepthTopAxis.Maximum = 0.650000000000000100
        DepthTopAxis.Minimum = -0.350000000000000000
        LeftAxis.LabelsOnAxis = False
        LeftAxis.LabelStyle = talValue
        LeftAxis.MinorTickCount = 0
        LeftAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1086#1076#1085#1086#1075' '#1090#1080#1087#1072' '#1072#1090#1086#1084#1086#1074
        RightAxis.MinorTickCount = 0
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        PrintMargins = (
          15
          21
          15
          21)
        object SelectAtomKindsSpeedButton: TSpeedButton
          Left = 0
          Top = 0
          Width = 167
          Height = 22
          Caption = #1042#1099#1073#1088#1072#1090#1100' '#1090#1080#1087#1099' '#1087#1086' '#1086#1089#1103#1084
          OnClick = SelectAtomKindsSpeedButtonClick
        end
        object RemovMarksCheckBox: TCheckBox
          Left = 171
          Top = 1
          Width = 108
          Height = 17
          Caption = #1059#1073#1088#1072#1090#1100' '#1085#1072#1076#1087#1080#1089#1080
          TabOrder = 0
          OnClick = RemovMarksCheckBoxClick
        end
        object ParametriсSeries: TFastLineSeries
          Marks.Arrow.Color = clBlack
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.HorizSize = 8
          Marks.Callout.Pen.Color = clDefault
          Marks.Callout.Style = psTriangle
          Marks.Callout.Visible = True
          Marks.Callout.Arrow.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Callout.ArrowHead = ahSolid
          Marks.Callout.Length = 25
          Marks.Visible = True
          SeriesColor = 8421631
          Title = #1055#1072#1088#1072#1084#1077#1090#1088#1080#1095#1077#1089#1082#1072#1103' '#1079#1072#1074#1080#1089#1080#1084#1086#1089#1090#1100
          LinePen.Color = 8421631
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
    object RoughnessTabSheet: TTabSheet
      Caption = #1064#1077#1088#1086#1093#1086#1074#1072#1090#1086#1089#1090#1100' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1080
      ImageIndex = 3
      object RoughnessChart: TChart
        Left = 0
        Top = 0
        Width = 895
        Height = 513
        Gradient.EndColor = 13556735
        Gradient.MidColor = 14739177
        Gradient.StartColor = 16774122
        Legend.Visible = False
        MarginBottom = 3
        MarginLeft = 1
        MarginRight = 4
        MarginTop = 3
        Title.Text.Strings = (
          #1043#1088#1072#1092#1080#1082' '#1096#1077#1088#1086#1093#1086#1074#1072#1090#1086#1089#1090#1080' '#1087#1086#1074#1077#1088#1093#1085#1086#1089#1090#1080' '#1086#1090' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1072' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072#1090#1086#1084#1086#1074)
        BottomAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1091#1076#1072#1083#1077#1085#1085#1099#1093' '#1072#1090#1086#1084#1086#1074
        LeftAxis.Title.Caption = #1064#1077#1088#1086#1093#1086#1074#1072#1090#1086#1089#1090#1100
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object RoughnessSeries: TAreaSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          SeriesColor = clRed
          AreaLinesPen.Visible = False
          Dark3D = False
          DrawArea = True
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          Transparency = 30
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
  end
end
