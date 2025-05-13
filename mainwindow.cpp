#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include "algo.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyIterator() {
    auto distance = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    ui->list_widget->setCurrentRow(distance);

    bool at_end = deque_model_.iterator == deque_model_.items.end();
    ui->btn_edit->setDisabled(at_end);
    ui->btn_erase->setDisabled(at_end);
    ui->btn_inc_iterator->setDisabled(at_end);
    ui->btn_dec_iterator->setDisabled(deque_model_.iterator == deque_model_.items.begin());
    ui->txt_elem_content->setText(at_end ? "" : QString::fromStdString(*deque_model_.iterator));
}

void MainWindow::ApplyModel() {
    auto it_tmp = deque_model_.iterator;
    int current_pos = it_tmp != deque_model_.items.end()
                          ? std::distance(deque_model_.items.begin(), it_tmp)
                          : -1;

    ui->list_widget->clear();

    int index = 0;
    for (const auto& elem : deque_model_.items) {
        ui->list_widget->addItem(QString::number(index) + ": " + QString::fromStdString(elem));
        ++index;
    }
    ui->list_widget->addItem("end");

    if (current_pos >= 0 && current_pos < static_cast<int>(deque_model_.items.size())) {
        deque_model_.iterator = deque_model_.items.begin() + current_pos;
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }

    ui->btn_pop_back->setDisabled(deque_model_.items.empty());
    ui->btn_pop_front->setDisabled(deque_model_.items.empty());
    ui->txt_size->setText(QString::number(deque_model_.items.size()));

    ApplyIterator();
}

void MainWindow::on_btn_push_back_clicked() {
    deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_push_front_clicked() {
    deque_model_.items.push_front(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_pop_back_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.items.pop_back();
    }
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_pop_front_clicked() {
    if (!deque_model_.items.empty()) {
        deque_model_.items.pop_front();
    }
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_dec_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.begin()) {
        --deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::on_btn_inc_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        ++deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow >= 0 && currentRow < static_cast<int>(deque_model_.items.size())) {
        deque_model_.iterator = deque_model_.items.begin() + currentRow;
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }
    ApplyIterator();
}

void MainWindow::on_btn_edit_clicked() {
    int row = ui->list_widget->currentRow();

    if (row >= 0 && row < static_cast<int>(deque_model_.items.size())) {
        deque_model_.items[row] = ui->txt_elem_content->text().toStdString();
        ApplyModel();
        ui->txt_elem_content->setText(QString::fromStdString(deque_model_.items[row]));
        ui->list_widget->setCurrentRow(row);
    }
}

void MainWindow::on_btn_end_clicked() {
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}

void MainWindow::on_btn_begin_clicked() {
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_erase_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        deque_model_.iterator = deque_model_.items.erase(deque_model_.iterator);
        if (deque_model_.iterator == deque_model_.items.end() && !deque_model_.items.empty()) {
            --deque_model_.iterator;
        }
        ApplyModel();
        ui->list_widget->setCurrentRow(0);
    }
}

void MainWindow::on_btn_insert_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        deque_model_.iterator = deque_model_.items.insert(deque_model_.iterator, ui->txt_elem_content->text().toStdString());
    } else {
        deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
        deque_model_.iterator = --deque_model_.items.end();
    }
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_resize_clicked() {
    deque_model_.items.resize(ui->txt_size->text().toInt());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_minel_clicked() {
    deque_model_.iterator = std::min_element(deque_model_.items.begin(), deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::on_btn_maxel_clicked() {
    deque_model_.iterator = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::on_btn_count_clicked() {
    std::string txt_to_find = ui->le_count->text().toStdString();
    auto result = std::count(deque_model_.items.begin(), deque_model_.items.end(), txt_to_find);
    ui->lbl_count->setText(QString::number(result));
}

void MainWindow::on_btn_find_clicked() {
    std::string txt_to_find = ui->txt_elem_content->text().toStdString();
    auto result = std::find(deque_model_.items.begin(), deque_model_.items.end(), txt_to_find);

    if(result != deque_model_.items.end()) {
        deque_model_.iterator = result;
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }
    ApplyIterator();
}

void MainWindow::on_btn_merge_sort_clicked() {
    std::string current_value;
    if (deque_model_.iterator != deque_model_.items.end()) {
        current_value = *deque_model_.iterator;
    }
    deque_model_.items = MergeSort(deque_model_.items, std::less<std::string>());

    if (!current_value.empty()) {
        deque_model_.iterator = std::find(deque_model_.items.begin(),
                                          deque_model_.items.end(),
                                          current_value);
    }
    if (deque_model_.iterator == deque_model_.items.end()) {
        deque_model_.iterator = deque_model_.items.begin();
    }

    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_merge_sort_nonereg_clicked() {
    std::string current_value;
    if (deque_model_.iterator != deque_model_.items.end()) {
        current_value = *deque_model_.iterator;
    }

    auto comp = [](const std::string& a, const std::string& b) {
        return QString::compare(QString::fromStdString(a),
                                QString::fromStdString(b),
                                Qt::CaseInsensitive) < 0;
    };

    deque_model_.items = MergeSort(deque_model_.items, comp);

    if (!current_value.empty()) {
        deque_model_.iterator = std::find(deque_model_.items.begin(),
                                          deque_model_.items.end(),
                                          current_value);
    }
    if (deque_model_.iterator == deque_model_.items.end()) {
        deque_model_.iterator = deque_model_.items.begin();
    }

    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_unique_clicked()
{
    int row = ui->list_widget->currentRow();

    if(std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())){
        auto to_del = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(to_del, deque_model_.items.end());
        ApplyIterator();
        ApplyModel();
        ui->list_widget->setCurrentRow(0);
    }else{
        ApplyModel();
        ui->list_widget->setCurrentRow(row);
    }
}

void MainWindow::SetRandomGen(const std::mt19937& random_gen) {
    gen_ = random_gen;
}

void MainWindow::on_btn_shuffle_clicked() {
    int row = ui->list_widget->currentRow();
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), gen_);
    ApplyModel();
    ui->list_widget->setCurrentRow(row);
}

void MainWindow::on_btn_tea_clicked() {
    deque_model_.items.clear();
    deque_model_.items.insert(deque_model_.items.end(), tea.begin(), tea.end());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_cakes_clicked() {
    deque_model_.items.clear();
    deque_model_.items.insert(deque_model_.items.end(), cakes.begin(), cakes.end());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ui->list_widget->setCurrentRow(0);
}

void MainWindow::on_btn_lower_bound_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    std::string value = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::lower_bound(deque_model_.items.begin(),
                                             deque_model_.items.end(),
                                             value);
    ApplyIterator();
}

void MainWindow::on_btn_upper_bound_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    std::string value = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::upper_bound(deque_model_.items.begin(),
                                             deque_model_.items.end(),
                                             value);
    ApplyIterator();
}

void MainWindow::on_btn_reverse_clicked() {
    int row = ui->list_widget->currentRow();
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
    ui->list_widget->setCurrentRow(row);
}

