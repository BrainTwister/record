#!groovy

pipeline {
  agent none
  stages {
    stage('Build-gcc-7') {
      agent {
        docker {
          image 'bernddoser/docker-devel-cpp:ubuntu-17.04-gcc-7-gtest-1.8.0'
          reuseNode true
        }
      }
      steps {
        sh '''
          mkdir -p build-gcc-7
          cd build-gcc-7
          cmake ..
          make 2>&1 |tee make.out
        '''
      }
      post {
        always {
          step([
            $class: 'WarningsPublisher', canComputeNew: false, canResolveRelativePaths: false,
            defaultEncoding: '', excludePattern: '', healthy: '', includePattern: '', messagesPattern: '',
            parserConfigurations: [[parserName: 'GNU Make + GNU C Compiler (gcc)', pattern: 'build-gcc-7/make.out']],
            unHealthy: ''
          ])
        }
      }
    }
    stage('Build-clang-4.0') {
      agent {
        docker {
          image 'bernddoser/docker-devel-cpp:ubuntu-16.04-clang-4.0-gtest-1.8.0'
          reuseNode true
        }
      }
      steps {
        sh '''
          mkdir -p build-clang-4.0
          cd build-clang-4.0
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
    stage('Test-gcc-7') {
      agent {
        docker {
          image 'bernddoser/docker-devel-cpp:ubuntu-17.04-gcc-7-gtest-1.8.0'
          reuseNode true
        }
      }
      steps {
        sh 'cd build-gcc-7 && make test'
      }
      post {
        always {
          step([
            $class: 'XUnitBuilder',
            thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
            tools: [[$class: 'GoogleTestType', pattern: 'build-gcc-7/Testing/*.xml']]
          ])
        }
      }
    }
    stage('Test-clang-4.0') {
      agent {
        docker {
          image 'bernddoser/docker-devel-cpp:ubuntu-16.04-clang-4.0-gtest-1.8.0'
          reuseNode true
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
    stage('Deploy') {
      agent {
        docker {
          image 'bernddoser/docker-devel-cpp:ubuntu-17.04-gcc-7-gtest-1.8.0'
          reuseNode true
        }
      }
      steps {
        sh 'cd build-gcc-7 && make package'
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

