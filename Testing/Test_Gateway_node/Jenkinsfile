pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/DaniRuan/Automatizacion_pruebas/tree/main/Testing/Test_Gateway_node'
            }
        }
        stage('Build') {
            steps {
                bat 'echo System testing started...'
            }
        }
        stage('Test') {
            steps {
                bat 'pio test -vvv'
            }
        }
    }
}