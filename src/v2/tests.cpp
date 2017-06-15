#include "tests.h"

void test_search()
{
    BooruSite* site = new BooruSite(string("Safebooru"),string("http://safebooru.org"), API::GELBOORU);

    cout << "Site " << site->getName() << " has search url " << site->getSearchUrl() << endl;

    BooruSearchEngine *engine = new BooruSearchEngine(site);

    engine->search("moriya_suwako",0,15);
}

void test_site()
{
    BooruSite* site = new BooruSite(string("Safebooru"),string("http://safebooru.org"), API::GELBOORU);

    cout << "Site " << site->getName() << " has search url " << site->getSearchUrl() << endl;
}

void test_database()
{
    BoorusDatabase *db = new BoorusDatabase();

    BooruSite* saf = new BooruSite(string("Safebooru"),string("http://safebooru.org"), API::GELBOORU);
    BooruSite* kon = new BooruSite(string("Konachan"),string("http://konachan.net"), API::MOEBOORU);

    db->addBooru(saf);
    db->addBooru(kon);

    std::vector<BooruSite*> sites = db->loadBoorus();

    cout << sites.size() << " boorus loaded" << endl;
}

void test_picture()
{
    QBooruPicture *p = new QBooruPicture;
    p->setText("Test Comment");
    p->show();
}

void test_maingrid()
{
    BooruSite* site = new BooruSite(string("Safebooru"),string("http://safebooru.org"), API::GELBOORU);
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