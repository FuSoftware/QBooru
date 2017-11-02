#include "tests.h"

#include "view/qboorutab.h"
#include "mainwidget.h"

void test_search()
{
    BooruSite* site = new BooruSite(string("Safebooru"),std::string("http://safebooru.org"), API::GELBOORU);

    cout << "Site " << site->getName() << " has search url " << site->getSearchUrl() << endl;

    BooruSearchEngine *engine = new BooruSearchEngine(site);

    engine->search("moriya_suwako",0,15);
}

void test_site()
{
    BooruSite* site = new BooruSite(std::string("Safebooru"),std::string("http://safebooru.org"), API::GELBOORU);

    cout << "Site " << site->getName() << " has search url " << site->getSearchUrl() << endl;
}

void test_database()
{
    BoorusDatabase *db = new BoorusDatabase();

    BooruSite* saf = new BooruSite(std::string("Safebooru"),std::string("http://safebooru.org"), API::GELBOORU);
    BooruSite* kon = new BooruSite(std::string("Konachan"),std::string("http://konachan.net"), API::MOEBOORU);

    db->addBooru(saf);
    db->addBooru(kon);

    std::vector<BooruSite*> sites = db->loadBoorus();

    cout << sites.size() << " boorus loaded" << endl;
}

void test_picture()
{
    BooruSite* saf = new BooruSite(std::string("Safebooru"),std::string("http://safebooru.org"), API::GELBOORU);

    BooruSearchEngine *engine = new BooruSearchEngine(saf);

    std::vector<BooruPicture*> pics = engine->search("hatsune_miku",0,15);

    std::cout << "Test : " << pics.size() << " pics" << std::endl;

    if(!pics.empty()){
        QBooruPicture *p = new QBooruPicture;
        p->setBooruPicture(pics.at(0));
        p->show();
    }else{
        exit(-1);
    }
}

void test_maingrid()
{
    BooruSite* site = new BooruSite(std::string("Safebooru"),std::string("http://safebooru.org"), API::GELBOORU);
    cout << "Site " << site->getName() << " loaded" << endl;

    BooruSearchEngine *engine = new BooruSearchEngine(site);
    cout << "Engine loaded" << endl;

    vector<BooruPicture*> pics = engine->search("kawashiro_nitori",0,15);
    cout << pics.size() << " pics loaded" << endl;

    QMainGrid *grid = new QMainGrid(5,3);
    cout << "Widget initialized" << endl;

    grid->loadPictures(pics);
    cout << "Pictures loaded" << endl;

    grid->show();
}

void test_simple_tab()
{
    qRegisterMetaType<QVector<BooruPicture*> >("QVector<BooruPicture*>");

    //Webiste
    BooruSite* site = new BooruSite(std::string("Yandere"),std::string("https://yande.re"), API::MOEBOORU);
    cout << "Site " << site->getName() << " loaded" << endl;

    //Widgets
    QBooruTab *t = new QBooruTab(site, 0);
    t->show();
}

void test_sample_boorus()
{
    qRegisterMetaType<QVector<BooruPicture*> >("QVector<BooruPicture*>");
    QVector<BooruSite*> boorus;

    boorus.push_back(new BooruSite(std::string("Yandere"),std::string("https://yande.re"), API::MOEBOORU));
    boorus.push_back(new BooruSite(std::string("Konachan"),std::string("https://konachan.com"), API::MOEBOORU));
    boorus.push_back(new BooruSite(std::string("Safebooru"),std::string("http://safebooru.org"), API::GELBOORU));
    boorus.push_back(new BooruSite(std::string("E621"),std::string("https://e621.net"), API::E621));

    MainWidget *w = new MainWidget();
    w->loadBoorus(boorus);
    w->show();
}
