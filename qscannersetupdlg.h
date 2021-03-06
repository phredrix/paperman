/***************************************************************************
                          qscannersetupdlg.h  -  description
                             -------------------
    begin                : Thu Jun 29 2000
    copyright            : (C) 2000 by M. Herder
    email                : crapsite@gmx.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2 as     *
 *   published by the Free Software Foundation.                            *
 *                                                                         *
 ***************************************************************************/

#ifndef QSCANNERSETUPDLG_H
#define QSCANNERSETUPDLG_H

#include <qdialog.h>
#include <qmap.h>
//Added by qt3to4:
#include <QShowEvent>
#include <QTranslator>
/**
  *@author M. Herder
  */
//forward declarations
class QRadioButton;
class QWidget;
class Q3ListView;
class Q3ListViewItem;
class QPushButton;
class QString;
class QScanner;
class QScanDialog;
class QTranslator;

class QScannerSetupDlg : public QDialog
{
Q_OBJECT
public:
  QScannerSetupDlg(QScanner *sc=0, QWidget *parent=0, const char *name=0,
                   bool modal=FALSE, Qt::WFlags f=0);
  ~QScannerSetupDlg();
  /**  */
  void addLVItem(QString name,QString vendor,QString model,QString type);
  /**  */
  void clearList();
  /**  */
  QString device();
  /**  */
  QString lastDevice();
  /**  */
  virtual void show();
  /**  */
  QMap <QString,QString> optionMap();

  QScanner *scanner (void) { return mpScanner; }

  bool setupLast();

  /** */
  static void initConfig();
private:
  /** */
  int mStyle;
  /**  */
  QMap <QString,QString> mOptionMap;
  /**  */
  QScanner* mpScanner;
  /**  */
  Q3ListView* mpListView;
  QPushButton *mpQuitButton;
  /**  */
  QPushButton* mpDeviceButton;
  /**  */
  QPushButton* mpLocalDeviceButton;
  /**  */
  QRadioButton* mpLastDeviceRadio;
  /**  */
  QRadioButton* mpLocalDevicesRadio;
  /**  */
  QRadioButton* mpAllDevicesRadio;
  /**  */
  QRadioButton* mpSameDeviceRadio;
  /**  */
  Q3ListViewItem* mpLastItem;
  /**  */
  int mQueryType;
  /**  */
  QPushButton* mpSelectButton;
  /** */
  QScanDialog* mpScanDialog;
  /** */
  QString mSanePath;
  /** */
  bool mProcessExit;
private://methods
  /** */
  void initScanner();
  /**  */
  void initDialog();
  /**  */

  void createContents(bool intcall);
  /**  */
  void createWhatsThisHelp();
  /** Open the device settings file, if it exists at all.
      This file is in XML format. If there are saved
      settings for the currently listed devices, list them
      as childitems of the device entries. */
  void loadDeviceSettings();
  /** No descriptions */
  void loadBackendTranslation(QString name);
  /** No descriptions */
  void markLastDevice();
protected: // Protected methods
  /**  */
  virtual void showEvent(QShowEvent * e);
public slots:
  void slotChangeStyle(int s);
private slots: // Private slots
  /**  */
  void slotDeviceSelected();
  /**  */
  void slotDeviceSelected(Q3ListViewItem*);
  /**  */
  void slotListViewClicked(Q3ListViewItem*);
  /**  */
  void slotAllDevices();
  /**  */
  void slotLocalDevices();
  /**  */
  void slotDeviceGroup(int);
  /**  */
  void slotProcessEvents();
  /**  */
  void slotQuit();
};

#endif
