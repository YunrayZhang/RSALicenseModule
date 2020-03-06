pipeline{
    agent{
        node{
            label 'master'
            customWorkspace '/DATA/rtklib-ci-workspace'
        }
    }
    stages{
        stage('Build'){
            steps{
                echo 'start to compile and package the rtklib'
                sh 'mkdir build'
                sh 'cd build&&cmake ../CMakeList.txt'
                sh 'cd build&&make'
            }  
        }
        stage('Deployment'){
            steps{
                echo 'Deployment rtklib into test bed'
            }
        }
        stage('Run Test'){
            steps{
                echo 'Run test for rtklib'
            }
        }
        stage('Send Report'){
            steps{
                echo 'Distributing test reports to stakholders'
            }
        }
        stage('Done'){
            steps{
                echo 'CI complete successfully'
            }
        }
    }
}
