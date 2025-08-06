#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QStackedWidget>
#include <QLineEdit>
#include <QIntValidator>
#include <QFont>
#include <iostream>
#include <QFontDatabase>
#include <QFile>
#include "Agent.h"
#include "AgentList.h"

/** ZZZ Builder
 * 
 * Creates a panel of agents from Zenless Zone Zero, allowing the user to
 * select the agents they would like to include.
 * Clicking the arrow swaps to a panel where the user inputs an integer 1-5, indicating
 * the number of teams they want to create
 * Hitting the Create Teams button generates this number of teams without any duplicate agents
 */

int main(int argc, char *argv[]) {
    AgentList list;
    list.generateList();
    std::vector<Agent>& agents = list.getList();

    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("ZZZ Builder");
    app.setWindowIcon(QIcon("images/app_icon.png"));
    window.setFixedSize(625, 725);
    
    // setting ZZZ font
    int font_id = QFontDatabase::addApplicationFont(":/fonts/ZZZFont.ttf");
    QString font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    QFont custom_font(font_family, 10);
    custom_font.setBold(true);
    app.setFont(custom_font);

    QHBoxLayout* layout = new QHBoxLayout();

    // AGENT PANEL
    QWidget* agent_widget = new QWidget();
    QVBoxLayout* agent_layout = new QVBoxLayout();
    QLabel* instructions = new QLabel("CHOOSE YOUR AGENTS:");
    QGridLayout* agent_grid = new QGridLayout();

    for (int i = 0; i < list.size(); i++) {
        Agent& agent = agents[i];
        QString image_path = "images/agents/" + QString::fromStdString(agent.getName()) + ".jpg";

        QToolButton* button = new QToolButton();
        button->setText(QString::fromStdString(agent.getName()));
        button->setIcon(QIcon(image_path));
        button->setIconSize(QSize(70, 70));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setFixedSize(80,95);
        button->setStyleSheet("font-size: 8pt");
        
        // connecting buttons to agent icons
        QObject::connect(button, &QToolButton::clicked, [&, button]() {
            if (agent.getStatus() == false) {
                agent.setStatus(true);
                button->setStyleSheet("font-size: 8pt; background-color: #026312;");
            } else {
                agent.setStatus(false);
                button->setStyleSheet("font-size: 8pt");
            }
            qDebug() << "toggled" << agent.getName() << "to" << agent.getStatus();
        });

        int row = i / 6;
        int col = i % 6;
        agent_grid->addWidget(button, row, col);
    }

    agent_layout->addWidget(instructions);
    agent_layout->addLayout(agent_grid);
    agent_widget->setLayout(agent_layout);

    // TEAMS PANEL
    QWidget* teams_widget = new QWidget();
    teams_widget->setFixedSize(500, 700);

    QLineEdit* num_teams_box = new QLineEdit();
    num_teams_box->setPlaceholderText("# of teams (1-5)");
    num_teams_box->setValidator(new QIntValidator(1, 5));
    num_teams_box->setFixedWidth(160);

    QToolButton* create_teams_button = new QToolButton();
    create_teams_button->setText("CREATE TEAMS");

    QVBoxLayout* teams_display_layout = new QVBoxLayout();
    QWidget* teams_display_widget = new QWidget();
    teams_display_widget->setLayout(teams_display_layout);

    QVBoxLayout* teams_layout = new QVBoxLayout();
    teams_layout->addWidget(num_teams_box);
    teams_layout->addWidget(create_teams_button);
    teams_layout->addWidget(teams_display_widget);
    teams_widget->setLayout(teams_layout);

    QVector<QWidget*> team_rows;
    QVector<QToolButton*> team_image_boxes;

    int num_teams;
    // changes # of teams displayed when num teams box is changed
    QObject::connect(num_teams_box, &QLineEdit::textChanged, [=, &team_rows, &team_image_boxes, &num_teams](const QString& input) {
        for (QWidget* row : team_rows) {
            teams_display_layout->removeWidget(row);
            row->deleteLater();
        }
        team_rows.clear();
        team_image_boxes.clear();

        bool ok;
        num_teams = input.toInt(&ok);
        if (!ok || num_teams < 1 || num_teams > 5) {
            qDebug("invalid num teams or empty");
            return;
        } else {
            qDebug() << "set:" << num_teams << "teams";
        }

        for (int team_idx = 0; team_idx < num_teams; ++team_idx) {
            QWidget* team_row = new QWidget();
            QHBoxLayout* row_layout = new QHBoxLayout();

            QLabel* team_label = new QLabel(QString("Team %1").arg(team_idx + 1));
            team_label->setFixedWidth(60);
            row_layout->addWidget(team_label);

            for (int i = 0; i < 3; ++i) {
                QToolButton* image_button = new QToolButton();
                image_button->setFixedSize(100, 100);
                image_button->setIconSize(QSize(100, 100));
                image_button->setStyleSheet("border: none; background: transparent;");
                row_layout->addWidget(image_button);
                team_image_boxes.append(image_button);
            }

            team_row->setLayout(row_layout);
            teams_display_layout->addWidget(team_row);
            team_rows.push_back(team_row);
        }
    });

    // create teams button
    QObject::connect(create_teams_button, &QToolButton::clicked, [=, &list, &team_image_boxes]() {
        // clear icons
        for (QToolButton* box : team_image_boxes) {
            box->setIcon(QIcon());
        }

        bool ok;
        int requested_teams = num_teams_box->text().toInt(&ok);
        if (!ok || requested_teams < 1 || requested_teams > 5) {
            qDebug() << "Invalid number of teams requested";
            return;
        }

        std::vector<Agent> completed_teams = list.generateTeams(requested_teams);

        for (int i = 0; i < team_image_boxes.size() && i < (int)completed_teams.size(); ++i) {
            QString img_path = "images/agents/" + QString::fromStdString(completed_teams[i].getName()) + ".jpg";
            team_image_boxes[i]->setIcon(QIcon(img_path));
        }
    });

    QStackedWidget* stacked_widget = new QStackedWidget();
    stacked_widget->setFixedSize(500, 700);
    stacked_widget->addWidget(agent_widget);
    stacked_widget->addWidget(teams_widget);

    QPushButton* toggle = new QPushButton("▶");
    toggle->setFixedSize(30, 60);

    // toggle button between agents and teams
    QObject::connect(toggle, &QPushButton::clicked, [=]() {
        int current = stacked_widget->currentIndex();
        if (current == 0) {
            stacked_widget->setCurrentIndex(1);
            toggle->setText("◀");
        } else {
            stacked_widget->setCurrentIndex(0);
            toggle->setText("▶");
        }
        qDebug() << "toggled overlay to" << current;
    });

    layout->addWidget(stacked_widget);
    layout->addWidget(toggle);
    window.setLayout(layout);
    window.show();

    return app.exec();
}
