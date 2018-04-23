#!groovy

pipeline {

  agent {
    label 'docker'
  }

  options {
    timeout(time: 1, unit: 'HOURS')
  }

  stages {
    stage('Build') {
      parallel {
        stage('gcc-5') {
          agent {
            docker {
              reuseNode true
              image 'braintwister/ubuntu-16.04-cmake-3.11-gcc-5-conan-1.2'
            }
          }
          steps {
            sh './build.sh gcc-5'
          }
          post {
            always {
              step([
                $class: 'WarningsPublisher', canComputeNew: false, canResolveRelativePaths: false,
                defaultEncoding: '', excludePattern: '', healthy: '', includePattern: '', messagesPattern: '',
                parserConfigurations: [[parserName: 'GNU Make + GNU C Compiler (gcc)', pattern: 'build-gcc-5/make.out']],
                unHealthy: ''
              ])
            }
          }
        }
        stage('clang-4') {
          agent {
            docker {
              reuseNode true
              image 'braintwister/ubuntu-16.04-cmake-3.11-clang-4-conan-1.2'
            }
          }
          steps {
            sh './build.sh clang-4'
          }
          post {
            always {
              step([
                $class: 'WarningsPublisher', canComputeNew: false, canResolveRelativePaths: false,
                defaultEncoding: '', excludePattern: '', healthy: '', includePattern: '', messagesPattern: '',
                parserConfigurations: [[parserName: 'Clang (LLVM based)', pattern: 'build-clang-4/make.out']],
                unHealthy: ''
              ])
            }
          }
        }
      }
    }
    stage('Test') {
      parallel {
        stage('gcc-5') {
          agent {
            docker {
              reuseNode true
              image 'braintwister/ubuntu-16.04-cmake-3.11-gcc-5-conan-1.2'
            }
          }
          steps {
            sh 'cd build-gcc-5 && make test'
          }
          post {
            always {
              step([
                $class: 'XUnitBuilder',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: 'build-gcc-5/Testing/*.xml']]
              ])
            }
          }
        }
        stage('clang-4') {
          agent {
            docker {
              reuseNode true
              image 'braintwister/ubuntu-16.04-cmake-3.11-clang-4-conan-1.2'
            }
          }
          steps {
            sh 'cd build-clang-4 && make test'
          }
          post {
            always {
              step([
                $class: 'XUnitBuilder',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: 'build-clang-4/Testing/*.xml']]
              ])
            }
          }
        }
      }
    }
    stage('Deploy') {
      agent {
        docker {
          reuseNode true
          image 'braintwister/ubuntu-16.04-cmake-3.11-gcc-5-conan-1.2'
        }
      }
      steps {
        sh 'cd build-gcc-5 && make package'
      }
      post {
        success {
          archiveArtifacts artifacts: "build*/cpp-settings*", fingerprint: true
        }
      }
    }
  }
  post {
    success {
      mail to: 'bernd.doser@braintwister.eu', subject: "SUCCESS: ${currentBuild.fullDisplayName}", body: "Success: ${env.BUILD_URL}"
    }
    failure {
      mail to: 'bernd.doser@braintwister.eu', subject: "FAILURE: ${currentBuild.fullDisplayName}", body: "Failure: ${env.BUILD_URL}"
    }
  }
}
