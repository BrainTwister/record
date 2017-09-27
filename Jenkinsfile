#!groovy

pipeline {
  agent {
    label 'docker'
  }
  environment {
    MYWORKSPACE = ${env.WORKSPACE}
  }
  stages {
    stage('Prepare') {
      steps {
        echo "WORKSPACE ${env.WORKSPACE}"
        echo "MYWORKSPACE ${MYWORKSPACE}"
        echo "BUILD_URL ${env.BUILD_URL}"
      }
    }
    stage('Build') {
      parallel {
        stage('gcc-5') {
          agent {
            docker {
              reuseNode true
              image 'bernddoser/docker-devel-cpp:ubuntu-16.04-gcc-5-conan-0.26.1'
              args "--env CONAN_USER_HOME=${MYWORKSPACE}"
            }
          }
          steps {
            sh '''
              rm -fr build-gcc-5
              mkdir -p build-gcc-5
              cd build-gcc-5
              conan install .. --build=missing -s compiler.libcxx=libstdc++11
              cmake ..
              make 2>&1 |tee make.out
            '''
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
        stage('clang-4.0') {
          agent {
            docker {
              reuseNode true
              image 'bernddoser/docker-devel-cpp:ubuntu-16.04-clang-4.0-conan-0.26.1'
              args "--env CONAN_USER_HOME=${env.WORKSPACE}"
            }
          }
          steps {
            sh '''
              rm -fr build-clang-4.0
              mkdir -p build-clang-4.0
              cd build-clang-4.0
              conan install .. --build=missing -s compiler.libcxx=libstdc++11
              cmake ..
              make 2>&1 |tee make.out
            '''
          }
          post {
            always {
              step([
                $class: 'WarningsPublisher', canComputeNew: false, canResolveRelativePaths: false,
                defaultEncoding: '', excludePattern: '', healthy: '', includePattern: '', messagesPattern: '',
                parserConfigurations: [[parserName: 'Clang (LLVM based)', pattern: 'build-clang-4.0/make.out']],
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
              image 'bernddoser/docker-devel-cpp:ubuntu-16.04-gcc-5-conan-0.26.1'
              args "--env CONAN_USER_HOME=${env.WORKSPACE}"
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
        stage('clang-4.0') {
          agent {
            docker {
              reuseNode true
              image 'bernddoser/docker-devel-cpp:ubuntu-16.04-clang-4.0-conan-0.26.1'
              args "--env CONAN_USER_HOME=${env.WORKSPACE}"
            }
          }
          steps {
            sh 'cd build-clang-4.0 && make test'
          }
          post {
            always {
              step([
                $class: 'XUnitBuilder',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: 'build-clang-4.0/Testing/*.xml']]
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
          image 'bernddoser/docker-devel-cpp:ubuntu-16.04-gcc-5-conan-0.26.1'
          args "--env CONAN_USER_HOME=${env.WORKSPACE}"
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
