class File { // base class
public:
    File(string name);
    virtual ~File();
    string name() const;
    virtual void open() const = 0; // pure virtual function
    virtual void redisplay() const;
private:
    string m_name;
};

File::File(string name) : m_name(name) {}

string File::name() const {
    return m_name;
}

void File::redisplay() const {
    cout << "refresh the screen";
}

File::~File() {}






class TextMsg : public File {
public:
    TextMsg(string name);
    ~TextMsg();
    virtual void open() const;
};

TextMsg::TextMsg(string name) : File(name) {}

TextMsg::~TextMsg() {
    cout << "Destroying " << File::name() << ", a text message" << endl;
}

void TextMsg::open() const {
    cout << "open text message";
}




class Video : public File {
public:
    Video(string name, int seconds);
    ~Video();
    virtual void open() const;
    virtual void redisplay() const;
private:
    int m_seconds;
};

Video::Video(string name, int seconds) : File(name), m_seconds(seconds) {}

Video::~Video() {
    cout << "Destroying " << File::name() << ", a video" << endl;
}

void Video::open() const {
    cout << "play " << m_seconds << " second video";
}

void Video::redisplay() const {
    cout << "replay video";
}


class Picture : public File {
public:
    Picture(string name);
    ~Picture();
    virtual void open() const;
private:
};

Picture::Picture(string name) : File(name) {}

Picture::~Picture() {
    cout << "Destroying the picture " << File::name() << endl;
}

void Picture::open() const {
    cout << "show picture";
}


void openAndRedisplay(const File* f)
{
    cout << f->name() << ": ";
    f->open();
    cout << endl << "Redisplay: ";
    f->redisplay();
    cout << endl;
}
