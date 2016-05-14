object RNGsProbabilityDistributionForm: TRNGsProbabilityDistributionForm
  Left = 0
  Top = 0
  Caption = #1056#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1074#1077#1088#1086#1103#1090#1085#1086'c'#1090#1077#1081' '#1043#1057#1063
  ClientHeight = 541
  ClientWidth = 909
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DistributionChart: TChart
    Left = 0
    Top = 41
    Width = 909
    Height = 500
    Legend.Visible = False
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    BottomAxis.Title.Caption = #1063#1080#1089#1083#1086
    LeftAxis.AxisValuesFormat = '#,##0.#####'
    LeftAxis.Title.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086
    View3D = False
    Align = alClient
    TabOrder = 0
    PrintMargins = (
      15
      24
      15
      24)
    object DistributionSeries: TAreaSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      DrawArea = True
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      Stairs = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
      Data = {
        001A0000000000000000003E4000000000000024400000000000804140000000
        0000002440000000000040404000000000004050400000000000004440000000
        0000005940000000000000144000000000000059400000000000002440000000
        0000C04C40000000000020574000000000008036400000000000803640000000
        0000906040000000000040454000000000003061400000000000706C40000000
        000010634000000000004060400000000000E050400000000000004940000000
        000020524000000000002057400000000000004940}
    end
    object AverageSeries: TLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      DataSource = DistributionSeries
      Title = 'AverageSeries'
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
      object AverageTeeFunction: TAverageTeeFunction
      end
    end
  end
  object InputDataPanel: TPanel
    Left = 0
    Top = 0
    Width = 909
    Height = 41
    Align = alTop
    TabOrder = 1
    ExplicitTop = -6
    object ModLabel: TLabel
      Left = 16
      Top = 14
      Width = 39
      Height = 13
      Caption = #1052#1086#1076#1091#1083#1100
    end
    object StartSpeedButton: TSpeedButton
      Left = 160
      Top = 10
      Width = 89
      Height = 22
      Caption = #1053#1072#1095#1072#1090#1100
      OnClick = StartSpeedButtonClick
    end
    object StopSpeedButton: TSpeedButton
      Left = 255
      Top = 10
      Width = 89
      Height = 22
      Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100
      OnClick = StopSpeedButtonClick
    end
    object GenLabel: TLabel
      Left = 632
      Top = 2
      Width = 120
      Height = 13
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1075#1077#1085#1077#1088#1072#1094#1080#1081':'
    end
    object GenCntLabel: TLabel
      Left = 758
      Top = 2
      Width = 4
      Height = 13
      Caption = '-'
    end
    object PauseGenLabel: TLabel
      Left = 632
      Top = 22
      Width = 121
      Height = 13
      Caption = #1055#1072#1091#1079#1072' '#1085#1072' '#1075#1077#1085#1077#1088#1072#1094#1080#1080' '#8470':'
    end
    object ModEdit: TEdit
      Left = 61
      Top = 11
      Width = 76
      Height = 21
      TabOrder = 0
      Text = '500'
    end
    object InitRNGCheckBox: TCheckBox
      Left = 350
      Top = 13
      Width = 123
      Height = 17
      Caption = #1048#1085#1080#1094#1080#1072#1083#1080#1079#1072#1094#1080#1103' '#1043#1057#1063
      TabOrder = 1
    end
    object RelativeScaleCheckBox: TCheckBox
      Left = 479
      Top = 13
      Width = 138
      Height = 17
      Caption = #1054#1090#1085#1086#1089#1080#1090#1077#1083#1100#1085#1072#1103' '#1096#1082#1072#1083#1072
      TabOrder = 2
      OnClick = RelativeScaleCheckBoxClick
    end
    object PauseGenEdit: TEdit
      Left = 758
      Top = 17
      Width = 123
      Height = 21
      TabOrder = 3
      Text = '0'
    end
  end
end
