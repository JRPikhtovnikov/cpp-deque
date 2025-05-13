#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>
#include <random>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetRandomGen(const std::mt19937& random_gen);

    void restore_iterator_after_operation(const std::string &value);
private slots:
    void on_btn_push_back_clicked();
    void on_btn_pop_back_clicked();
    void on_btn_push_front_clicked();
    void on_btn_pop_front_clicked();
    void on_btn_clear_clicked();
    void on_btn_dec_iterator_clicked();
    void on_btn_inc_iterator_clicked();
    void on_list_widget_currentRowChanged(int currentRow);
    void on_btn_edit_clicked();
    void on_btn_end_clicked();
    void on_btn_begin_clicked();
    void on_btn_erase_clicked();
    void on_btn_insert_clicked();
    void on_btn_resize_clicked();
    void on_btn_minel_clicked();
    void on_btn_maxel_clicked();
    void on_btn_count_clicked();
    void on_btn_find_clicked();
    void on_btn_merge_sort_clicked();
    void on_btn_merge_sort_nonereg_clicked();
    void on_btn_reverse_clicked();
    void on_btn_unique_clicked();
    void on_btn_shuffle_clicked();
    void on_btn_tea_clicked();
    void on_btn_cakes_clicked();
    void on_btn_lower_bound_clicked();
    void on_btn_upper_bound_clicked();

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model deque_model_;
    std::mt19937 gen_{std::random_device{}()};
    Ui::MainWindow *ui;
};
