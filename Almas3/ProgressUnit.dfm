object ProgressForm: TProgressForm
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1072#1103' '#1086#1087#1077#1088#1072#1094#1080#1103
  ClientHeight = 129
  ClientWidth = 285
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object OperationLabel: TLabel
    Left = 8
    Top = 8
    Width = 269
    Height = 13
    Caption = #1054#1087#1077#1088#1072#1094#1080#1103
  end
  object StateNameLabel: TLabel
    Left = 8
    Top = 27
    Width = 29
    Height = 13
    Caption = #1069#1090#1072#1087':'
  end
  object StateLabel: TLabel
    Left = 43
    Top = 27
    Width = 234
    Height = 13
    AutoSize = False
    Caption = 'StateLabel'
  end
  object OperationProgressBar: TProgressBar
    Left = 8
    Top = 56
    Width = 269
    Height = 17
    TabOrder = 0
  end
  object CancelBitBtn: TBitBtn
    Left = 104
    Top = 96
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 1
  end
end
