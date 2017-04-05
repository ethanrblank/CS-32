void listAll(const MenuItem* m, string path) { // two-parameter overload
    if (m == NULL)
        return;
    if (m->menuItems() != NULL) {
        for (vector<MenuItem*>::const_iterator p = m->menuItems()->begin(); p != m->menuItems()->end(); ++p) {
            if (path == "") {
                string output = path + (*p)->name();
                cout << output << endl;
                listAll(*p, output);
            }
            else {
                string output = path + "/" +  (*p)->name();
                cout << output << endl;
                listAll(*p, output);
            }
        }
    }
}
