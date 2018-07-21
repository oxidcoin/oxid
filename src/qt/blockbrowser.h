// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2018 Oxid developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BLOCKBROWSER_H
#define BLOCKBROWSER_H

#include "base58.h"
#include "clientmodel.h"
#include "main.h"
#include "wallet.h"
#include "walletmodel.h"
#include <QWidget>

#include <QDir>
#include <QFile>
#include <QMap>
#include <QProcess>
#include <QSettings>
#include <QSlider>
#include <QStringList>
#include <QTime>
#include <QTimer>

double getBlockHardness(int);
double getTxTotalValue(std::string);
double convertCoins(int64_t);
double getTxFees(std::string);
int getBlockTime(int);
int getBlocknBits(int);
int getBlockNonce(int);
int blocksInPastHours(int);
int getBlockHashrate(int);
std::string getInputs(std::string);
std::string getOutputs(std::string);
std::string getBlockHash(int);
std::string getBlockMerkle(int);
bool addnode(std::string);
const CBlockIndex* getBlockIndex(int);
int64_t getInputValue(CTransaction, CScript);


namespace Ui {
class BlockBrowser;
}
class WalletModel;

class BlockBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit BlockBrowser(QWidget *parent = 0);
    ~BlockBrowser();

    void setModel(WalletModel *model);

public slots:

    void blockClicked();
    void txClicked();
    void updateExplorer(bool);

private slots:

private:
    Ui::BlockBrowser *ui;
    WalletModel *model;

};

#endif // BLOCKBROWSER_H
