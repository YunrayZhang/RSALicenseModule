pipeline{
    agent{
        node{
            label 'master'
            customWorkspace '/DATA/rtklib-ci-workspace'
        }
    }
    stages{
        stage('Clean Workspace'){
            steps{
                echo 'clean the workspace'
                sh 'git clean -fdx'
            }
        }
        stage('Build'){
            steps{
                echo 'start to compile and package the rtklib'
                sh 'mkdir build'
                dir('build'){
                    sh 'cmake -e  ../'
                    sh 'make -f Makefile'
                }
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
                dir('build/output'){
                    sh './unittests'
                }
            }
        }
    }
    post {
        failure {
            mailext to: 'foolishx001@126.com',
                 subject: "Failure of RTK-lib Pipeline: ${currentBuild.fullDisplayName}",
                 body: "Something is wrong with ${env.BUILD_URL}"
                 memeType:'text/html'

        }
        success{
            mailext( to: 'foolishx001@126.com',
                subject: "Success of RTK-lib Pipeline: ${currentBuild.fullDisplayName}",
                body:"Everything goes well with ${env.BUILD_URL}",
                mimeType:'text/html')
        }
}
}
