#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>

const double G = 6.674e-11;
const double SOFTENING = 0.0001;

struct Particle {
    double mass;
    double x, y, z;
    double vx, vy, vz;
    double fx, fy, fz;
};

void createParticles(std::vector<Particle> &particles, int numParticles){
    std::random_device rndm;
    std::mt19937 gen(rndm());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    for (int i = 0; i < numParticles; i++){
        Particle p;
        p.mass = dis(gen);
        p.x = dis(gen);
        p.y = dis(gen);
        p.z = dis(gen);
        p.vx = dis(gen);
        p.vy = dis(gen);
        p.vz = dis(gen);
        p.fx = 0.0;
        p.fy = 0.0;
        p.fz = 0.0;
        particles.push_back(p);
    }

}

void calculateForces(std::vector<Particle> &particles){
    for (Particle &p : particles){
        p.fx = 0;
        p.fy = 0;
        p.fz = 0;
    }

    for(size_t i = 0; i < particles.size(); i++){
        for (size_t j = i + 1; j < particles.size(); j++){
            double dx = particles[j].x - particles[i].x;
            double dy = particles[j].y - particles[i].y;
            double dz = particles[j].z - particles[i].z;
            double distance = std::sqrt(dx * dx + dy * dy + dz * dz + SOFTENING);
            double force = (G * particles[i].mass * particles[j].mass) / (distance * distance);
            double fx = force * dx / distance;
            double fy = force * dy / distance;
            double fz = force * dz / distance;

            particles[i].fx += fx;
            particles[i].fy += fy;
            particles[i].fz += fz;
            particles[j].fx -= fx;
            particles[j].fy -= fy;            
            particles[j].fz -= fz;
        }

    }
}

void updatePosition(std::vector<Particle> &particles, double dt){
    for (Particle &p : particles){
        p.vx = p.vx + (p.fx / p.mass) * dt;
        p.vy = p.vy + (p.fy / p.mass) * dt;
        p.vz = p.vz + (p.fz / p.mass) * dt;
        p.x = p.x + p.vx * dt;
        p.y = p.y + p.vy * dt;
        p.z = p.z + p.vz * dt;
    }
}

void output(const std::vector<Particle> &particles, std::ofstream &out) {
    out << particles.size() << std::endl;
    for (const Particle &p : particles) {
        out << p.mass << "\t" << p.x << "\t" << p.y << "\t" << p.z
            << "\t" << p.vx << "\t" << p.vy << "\t" << p.vz
            << "\t" << p.fx << "\t" << p.fy << "\t" << p.fz << std::endl;
    }
}



int main(int argc, char *argv[]){
    if (argc < 5){
        std::cerr << "Usage: " << argv[0] << " <num_particles> <time_step> <num_iterations> <output_interval>" << std::endl;
        return 1;
    }

    int numParticles = std::stoi(argv[1]);
    double dt = std::stod(argv[2]);
    int numIterations = std::stoi(argv[3]);
    int outputInterval = std::stoi(argv[4]);

    std::vector<Particle> particles;
    createParticles(particles, numParticles);

    std::ofstream out("solar.tsv");

    for (int i = 0; i < numIterations; i++){
        calculateForces(particles);
        updatePosition(particles, dt);
        if (i % outputInterval == 0){
            output(particles, out);
        }
    }
    out.close();
    return 0;
}

