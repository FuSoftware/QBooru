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
