#include "mesh.h"

Mesh::Mesh(){}

Mesh::~Mesh(){}

double
Mesh::encontrarDeltaX()
{
  double xMax = vertex[0].position[0];
  double xMin = vertex[0].position[0];

  for (unsigned int i = 0; i < vertex.size(); ++i){
      if(vertex[i].position[0] < xMin){
        xMin = vertex[i].position[0];
      }
      if (vertex[i].position[0] > xMax)
      {
        xMax = vertex[i].position[0];
      }
  }
  this->xMin = xMin;

  return xMax - xMin;
}

double
Mesh::encontrarDeltaY()
{
  double yMax = vertex[0].position[1];
  double yMin = vertex[0].position[1];

  for (unsigned int i = 0; i < vertex.size(); ++i){
    if(vertex[i].position[1] < yMin){
      yMin = vertex[i].position[1];
    }
    if (vertex[i].position[1] > yMax){
      yMax = vertex[i].position[1];
    }
  }

  this->yMin = yMin;

  return yMax - yMin;
}

double
Mesh::encontrarDeltaZ()
{
  double zMax = vertex[0].position[2];
  double zMin = vertex[0].position[2];

  for (unsigned int i = 0; i < vertex.size(); ++i){
    if(vertex[i].position[2] < zMin){
        zMin = vertex[i].position[2];
    }
    if (vertex[i].position[2] > zMax){
        zMax = vertex[i].position[2];
    }
  }

  this->zMin = zMin;

  return zMax - zMin;
}

void
Mesh::carregarArquivo(string nomeArquivo)
{
  ifstream arquivo(nomeArquivo.c_str());
  string path = getPath(nomeArquivo);

  if(!arquivo.is_open())
  {
    cout << "Não foi possível abrir o aquivo!!!" << endl;
    exit(-1);
  }

  string tipo;
  string line;
  string trash;

  float x, y, z;

  while(getline(arquivo, line))
  {
    stringstream stream(line);

    if(line.substr(0, 6) == "mtllib")
    {
      stream >> trash >> this->fileMtl;
      this->fileMtl = path + this->fileMtl;
    }

    else if(line.substr(0, 2) == "v ")
    {
      stream >> trash >> x >> y >> z;
      this->vertex.push_back(Vertex(x, y, z, 100, 100, 100, 100));
    }

    else if(line.substr(0,2) == "vn")
    {
      stream >> trash >> x >> y >> z;
      this->normal.push_back(Vertex(x, y, z));
    }

    else if(line.substr(0,2) == "vt")
    {
      stream >> trash >> x >> y;
      this->texture.push_back(Vertex2D(x, y));
    }

    else if(line.substr(0,2) == "f ")
    {
      unsigned int v, n, t;
      char c_trash;

      stream >> trash;
      for(int i = 0; i < 3; i++)
      {
        if(!this->vertex.empty())
        {
          v = 1;
          stream >> v;
          this->vertexIndex.push_back(v-1);
        }

        stream >> c_trash;

        if(!this->normal.empty())
        {
          n = 1;
          stream >> n;
          this->normalIndex.push_back(n-1);
        }

        stream >> c_trash;

        if(!this->texture.empty())
        {
          t = 1;
          stream >> t;
          this->textureIndex.push_back(t-1);
        }
      }
    }
  }

  // cout << this->vertexIndex.size() << endl;

  // for(unsigned int i = 0; i < this->vertexIndex.size() / 3; i++)
  // {
  //   cout << "f " << this->vertexIndex[(i * 2) + i + 0] << '/' << this->normalIndex[(i * 2) + i + 0] << '/' << this->textureIndex[(i * 2) + i + 0] << ' ';
  //   cout << this->vertexIndex[(i * 2) + i + 1] << '/' << this->normalIndex[(i * 2) + i + 1] << '/' << this->textureIndex[(i * 2) + i + 1] << ' ';
  //   cout << this->vertexIndex[(i * 2) + i + 2] << '/' << this->normalIndex[(i * 2) + i + 2] << '/' << this->textureIndex[(i * 2) + i + 2] << ' ' << endl;
  // }

  // for(unsigned int i = 0; i < this->vertexIndex.size(); i += 3)
  // {
  //   cout << "f " << this->vertexIndex[i] << '/' << this->normalIndex[i] << '/' << this->textureIndex[i] << ' ';
  //   cout << this->vertexIndex[i+1] << '/' << this->normalIndex[i+1] << '/' << this->textureIndex[i+1] << ' ';
  //   cout << this->vertexIndex[i+2] << '/' << this->normalIndex[i+2] << '/' << this->textureIndex[i+2] << ' ' << endl;
  // }

    this->deltaX = this->encontrarDeltaX();
    this->deltaY = this->encontrarDeltaY();
    this->deltaZ = this->encontrarDeltaZ();
  arquivo.close();
cout << this->vertex.size();
  //carregarMaterial(this->fileMtl);
}

string
Mesh::getPath(string fileName)
{
  for(int i = (int)fileName.size() - 1; i >= 0; i--)
  {
    if(fileName[i] == '/') {
      return fileName.substr(0, i+1);
    }
  }

  return "";
}

void
Mesh::carregarMaterial(string nomeArquivo)
{
  ifstream arquivo(nomeArquivo.c_str());
  string path = getPath(nomeArquivo);

  if(!arquivo.is_open())
  {
    cout << "Não foi possível abrir o aquivo!!!" << endl;
    exit(-1);
  }

  string tipo;
  string line;
  string trash;

  // float x, y, z;

  this->material = vector<Material>();

  while(getline(arquivo, line))
  {
    bool copy = false;
    string temp = "";

    for(unsigned int i = 0; i < line.size(); i++)
    {
      if(isalnum(line[i]))
        copy = true;

      if(copy)
        temp += line[i];
    }
    line = temp;

    stringstream stream(line);

    if(line.substr(0, 6) == "newmtl")
    {
      this->material.push_back(Material());
      stream >> trash >> this->material.back().name;
    }
    else if(line.substr(0, 2) == "Ns")
    {
      stream >> trash >> this->material.back().ns;
    }
    else if(line.substr(0, 2) == "Ni")
    {
      stream >> trash >> this->material.back().ni;
    }
    else if(line.substr(0, 2) == "d ")
    {
      stream >> trash >> this->material.back().d;
    }
    else if(line.substr(0, 2) == "Tr")
    {
      stream >> trash >> this->material.back().tr;
    }
    else if(line.substr(0, 2) == "Tf")
    {
      stream >> trash >> this->material.back().tf[0];
      stream >> this->material.back().tf[1];
      stream >> this->material.back().tf[2];
    }
    else if(line.substr(0, 5) == "illum")
    {
      stream >> trash >> this->material.back().illum;
    }
    else if(line.substr(0, 2) == "Ka")
    {
      stream >> trash >> this->material.back().ka[0];
      stream >> this->material.back().ka[1];
      stream >> this->material.back().ka[2];
    }
    else if(line.substr(0, 2) == "Kd")
    {
      stream >> trash >> this->material.back().kd[0];
      stream >> this->material.back().kd[1];
      stream >> this->material.back().kd[2];
    }
    else if(line.substr(0, 2) == "Ks")
    {
      stream >> trash >> this->material.back().ks[0];
      stream >> this->material.back().ks[1];
      stream >> this->material.back().ks[2];
    }
    else if(line.substr(0, 2) == "Ke")
    {
      stream >> trash >> this->material.back().ke[0];
      stream >> this->material.back().ke[1];
      stream >> this->material.back().ke[2];
    }
    else if(line.substr(0, 6) == "map_Kd") //arcade
    // else if(line.substr(0, 8) == "map_bump") //gun8
    {
      stream >> trash >> this->material.back().fileName;
      this->material.back().fileName = path + this->material.back().fileName;

      this->material.back().imageID = loadImage(this->material.back().fileName.c_str());
      if(this->material.back().imageID == 0)
      {
        cout << "Error to load image: " << this->material.back().fileName << endl;
      }
      else
      {
        /*ilBindImage(this->material.back().imageID);
        this->material.back().imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
        this->material.back().imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);
        this->material.back().imageData = ilGetData();

        // cout << endl << "+----------------------------------+" << endl;
        // cout << "material.back().fileName: " << this->material.back().fileName << endl;
        // cout << "material.back().imageID: " << this->material.back().imageID << endl;
        // cout << "material.back().imageWidth: " << this->material.back().imageWidth << endl;
        // cout << "material.back().imageHeight: " << this->material.back().imageHeight << endl;
        */
      }
    }

  }

  arquivo.close();

}



int
Mesh::loadImage(string m_fileName)
{

  m_pImage = IMG_Load(m_fileName.c_str());


    if(m_pImage == NULL){
	printf("\n ERRO: Erro ao ler a imagem de textura %s\n %s\n\n", m_fileName.c_str(), SDL_GetError());
    }
   int Mode = GL_BGR;
   //int Mode = GL_RGB;
   if(m_pImage->format->BytesPerPixel == 4) {
   	 Mode = GL_RGBA;
   }
  /*ILboolean success;
  unsigned int imageID;

  // init DevIL. This needs to be done only once per application
  ilInit();
  // generate an image name
  ilGenImages(1, &imageID);
  // bind it
  ilBindImage(imageID);
  // match image origin to OpenGL’s
  ilEnable(IL_ORIGIN_SET);
  ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
  // load  the image
  success = ilLoadImage((ILstring)imageName.c_str());
  ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  // check to see if everything went OK
  if (!success) {
    ilDeleteImages(1, &imageID);
    return 0;
  }
  else return imageID;*/
}


void
Mesh::redimensionar()
{
    if(this->deltaX > this->deltaY && this->deltaX > this->deltaZ){
        for (unsigned int i = 0; i < this->vertex.size(); ++i){
            this->vertex[i].position[0] /= this->deltaX;
            this->vertex[i].position[1] /= this->deltaX;
            this->vertex[i].position[2] /= this->deltaX;
        }
    }
    else if(this->deltaY > this->deltaX && this->deltaY > this->deltaZ){
        for (unsigned int i = 0; i < this->vertex.size(); ++i){
            this->vertex[i].position[0] /= this->deltaY;
            this->vertex[i].position[1] /= this->deltaY;
            this->vertex[i].position[2] /= this->deltaY;
        }
    }
    else if(this->deltaZ > this->deltaY && this->deltaZ > this->deltaX){
        for (unsigned int i = 0; i < this->vertex.size(); ++i){
            this->vertex[i].position[0] /= this->deltaZ;
            this->vertex[i].position[1] /= this->deltaZ;
            this->vertex[i].position[2] /= this->deltaZ;
        }
    }
}

void
Mesh::transladar()
{
    double diffX = this->xMin + (this->deltaX/2);
    double diffY = this->yMin + (this->deltaY/2);
    double diffZ = this->zMin + (this->deltaZ/2);

    for (unsigned int i = 0; i < this->vertex.size(); ++i){
            this->vertex[i].position[0] -= diffX;
            this->vertex[i].position[1] -= diffY;
            this->vertex[i].position[2] -= diffZ;
    }
}

vector<Vertex> Mesh::getVertex() { return this->vertex; }
vector<unsigned int> Mesh::getIndice() { return this->indice; }
