
class Camera
{
private:
    Vector3d position; ///< Position de la caméra.
    Matrix44d viewMatrix; ///< Matrice de vue.
public:
    void setView(const Vector3d& position, const Vector3d& target, const Vector3d& up) {
        this->position = position;
        
        Vector3d f = position - target; f.unit();
        Vector3d s = f * up; s.unit();
        Vector3d u = s * f; u.unit();
        viewMatrix.loadView(f, s, u);
    }

    void applyView() {
        glMultMatrixd(viewMatrix.elements);
        glTranslated(-position.x, -position.y, -position.z);
    }
};
