#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);//qt的输入密码模式
    ui->confirm_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip_label->setProperty("state","normal");//错误提示刷新
    repolish(ui->err_tip_label);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_get_code_btn_clicked()
{
    auto email = ui->email_edit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match){
        //发送http验证码
    }else{
        showTip(tr("邮箱地址不正确"), false);
    }
}

void RegisterDialog::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->err_tip_label->setProperty("state","normal");
    }else{
        ui->err_tip_label->setProperty("state","err");
    }
    ui->err_tip_label->setText(str);
    repolish(ui->err_tip_label);
}

